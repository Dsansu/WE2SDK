/*
 * FreeRTOS Kernel V10.3.0
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

/* Standard includes. */
#include "../../ARM_CM55/secure/secure_heap.h"

#include <stdint.h>

/* Secure context heap includes. */
#include "../../ARM_CM55/secure/secure_port_macros.h"

/**
 * @brief Total heap size.
 */
#define secureconfigTOTAL_HEAP_SIZE		( ( ( size_t ) ( 10 * 1024 ) ) )

/* No test marker by default. */
#ifndef mtCOVERAGE_TEST_MARKER
	#define mtCOVERAGE_TEST_MARKER()
#endif

/* No tracing by default. */
#ifndef traceMALLOC
	#define traceMALLOC( pvReturn, xWantedSize )
#endif

/* No tracing by default. */
#ifndef traceFREE
	#define traceFREE( pv, xBlockSize )
#endif

/* Block sizes must not get too small. */
#define secureheapMINIMUM_BLOCK_SIZE	( ( size_t ) ( xHeapStructSize << 1 ) )

/* Assumes 8bit bytes! */
#define secureheapBITS_PER_BYTE			( ( size_t ) 8 )
/*-----------------------------------------------------------*/

/* Allocate the memory for the heap. */
#if( configAPPLICATION_ALLOCATED_HEAP == 1 )
	/* The application writer has already defined the array used for the RTOS
	 * heap - probably so it can be placed in a special segment or address. */
	extern uint8_t ucHeap[ secureconfigTOTAL_HEAP_SIZE ];
#else /* configAPPLICATION_ALLOCATED_HEAP */
	static uint8_t ucHeap[ secureconfigTOTAL_HEAP_SIZE ];
#endif /* configAPPLICATION_ALLOCATED_HEAP */

/**
 * @brief The linked list structure.
 *
 * This is used to link free blocks in order of their memory address.
 */
typedef struct A_BLOCK_LINK
{
	struct A_BLOCK_LINK *pxNextFreeBlock;	/**< The next free block in the list. */
	size_t xBlockSize;						/**< The size of the free block. */
} BlockLink_t;
/*-----------------------------------------------------------*/

/**
 * @brief Called automatically to setup the required heap structures the first
 * time pvPortMalloc() is called.
 */
static void prvHeapInit( void );

/**
 * @brief Inserts a block of memory that is being freed into the correct
 * position in the list of free memory blocks.
 *
 * The block being freed will be merged with the block in front it and/or the
 * block behind it if the memory blocks are adjacent to each other.
 *
 * @param[in] pxBlockToInsert The block being freed.
 */
static void prvInsertBlockIntoFreeList( BlockLink_t *pxBlockToInsert );
/*-----------------------------------------------------------*/

/**
 * @brief The size of the structure placed at the beginning of each allocated
 * memory block must by correctly byte aligned.
 */
static const size_t xHeapStructSize = ( sizeof( BlockLink_t ) + ( ( size_t ) ( secureportBYTE_ALIGNMENT - 1 ) ) ) & ~( ( size_t ) secureportBYTE_ALIGNMENT_MASK );

/**
 * @brief Create a couple of list links to mark the start and end of the list.
 */
static BlockLink_t xStart, *pxEnd = NULL;

/**
 * @brief Keeps track of the number of free bytes remaining, but says nothing
 * about fragmentation.
 */
static size_t xFreeBytesRemaining = 0U;
static size_t xMinimumEverFreeBytesRemaining = 0U;

/**
 * @brief Gets set to the top bit of an size_t type.
 *
 * When this bit in the xBlockSize member of an BlockLink_t structure is set
 * then the block belongs to the application. When the bit is free the block is
 * still part of the free heap space.
 */
static size_t xBlockAllocatedBit = 0;
/*-----------------------------------------------------------*/

static void prvHeapInit( void )
{
BlockLink_t *pxFirstFreeBlock;
uint8_t *pucAlignedHeap;
size_t uxAddress;
size_t xTotalHeapSize = secureconfigTOTAL_HEAP_SIZE;

	/* Ensure the heap starts on a correctly aligned boundary. */
	uxAddress = ( size_t ) ucHeap;

	if( ( uxAddress & secureportBYTE_ALIGNMENT_MASK ) != 0 )
	{
		uxAddress += ( secureportBYTE_ALIGNMENT - 1 );
		uxAddress &= ~( ( size_t ) secureportBYTE_ALIGNMENT_MASK );
		xTotalHeapSize -= uxAddress - ( size_t ) ucHeap;
	}

	pucAlignedHeap = ( uint8_t * ) uxAddress;

	/* xStart is used to hold a pointer to the first item in the list of free
	 * blocks.  The void cast is used to prevent compiler warnings. */
	xStart.pxNextFreeBlock = ( void * ) pucAlignedHeap;
	xStart.xBlockSize = ( size_t ) 0;

	/* pxEnd is used to mark the end of the list of free blocks and is inserted
	 * at the end of the heap space. */
	uxAddress = ( ( size_t ) pucAlignedHeap ) + xTotalHeapSize;
	uxAddress -= xHeapStructSize;
	uxAddress &= ~( ( size_t ) secureportBYTE_ALIGNMENT_MASK );
	pxEnd = ( void * ) uxAddress;
	pxEnd->xBlockSize = 0;
	pxEnd->pxNextFreeBlock = NULL;

	/* To start with there is a single free block that is sized to take up the
	 * entire heap space, minus the space taken by pxEnd. */
	pxFirstFreeBlock = ( void * ) pucAlignedHeap;
	pxFirstFreeBlock->xBlockSize = uxAddress - ( size_t ) pxFirstFreeBlock;
	pxFirstFreeBlock->pxNextFreeBlock = pxEnd;

	/* Only one block exists - and it covers the entire usable heap space. */
	xMinimumEverFreeBytesRemaining = pxFirstFreeBlock->xBlockSize;
	xFreeBytesRemaining = pxFirstFreeBlock->xBlockSize;

	/* Work out the position of the top bit in a size_t variable. */
	xBlockAllocatedBit = ( ( size_t ) 1 ) << ( ( sizeof( size_t ) * secureheapBITS_PER_BYTE ) - 1 );
}
/*-----------------------------------------------------------*/

static void prvInsertBlockIntoFreeList( BlockLink_t *pxBlockToInsert )
{
BlockLink_t *pxIterator;
uint8_t *puc;

	/* Iterate through the list until a block is found that has a higher address
	 * than the block being inserted. */
	for( pxIterator = &xStart; pxIterator->pxNextFreeBlock < pxBlockToInsert; pxIterator = pxIterator->pxNextFreeBlock )
	{
		/* Nothing to do here, just iterate to the right position. */
	}

	/* Do the block being inserted, and the block it is being inserted after
	 * make a contiguous block of memory? */
	puc = ( uint8_t * ) pxIterator;
	if( ( puc + pxIterator->xBlockSize ) == ( uint8_t * ) pxBlockToInsert )
	{
		pxIterator->xBlockSize += pxBlockToInsert->xBlockSize;
		pxBlockToInsert = pxIterator;
	}
	else
	{
		mtCOVERAGE_TEST_MARKER();
	}

	/* Do the block being inserted, and the block it is being inserted before
	 * make a contiguous block of memory? */
	puc = ( uint8_t * ) pxBlockToInsert;
	if( ( puc + pxBlockToInsert->xBlockSize ) == ( uint8_t * ) pxIterator->pxNextFreeBlock )
	{
		if( pxIterator->pxNextFreeBlock != pxEnd )
		{
			/* Form one big block from the two blocks. */
			pxBlockToInsert->xBlockSize += pxIterator->pxNextFreeBlock->xBlockSize;
			pxBlockToInsert->pxNextFreeBlock = pxIterator->pxNextFreeBlock->pxNextFreeBlock;
		}
		else
		{
			pxBlockToInsert->pxNextFreeBlock = pxEnd;
		}
	}
	else
	{
		pxBlockToInsert->pxNextFreeBlock = pxIterator->pxNextFreeBlock;
	}

	/* If the block being inserted plugged a gab, so was merged with the block
	 * before and the block after, then it's pxNextFreeBlock pointer will have
	 * already been set, and should not be set here as that would make it point
	 * to itself. */
	if( pxIterator != pxBlockToInsert )
	{
		pxIterator->pxNextFreeBlock = pxBlockToInsert;
	}
	else
	{
		mtCOVERAGE_TEST_MARKER();
	}
}
/*-----------------------------------------------------------*/

void *pvPortMalloc( size_t xWantedSize )
{
BlockLink_t *pxBlock, *pxPreviousBlock, *pxNewBlockLink;
void *pvReturn = NULL;

	/* If this is the first call to malloc then the heap will require
	 * initialisation to setup the list of free blocks. */
	if( pxEnd == NULL )
	{
		prvHeapInit();
	}
	else
	{
		mtCOVERAGE_TEST_MARKER();
	}

	/* Check the requested block size is not so large that the top bit is set.
	 * The top bit of the block size member of the BlockLink_t structure is used
	 * to determine who owns the block - the application or the kernel, so it
	 * must be free. */
	if( ( xWantedSize & xBlockAllocatedBit ) == 0 )
	{
		/* The wanted size is increased so it can contain a BlockLink_t
		 * structure in addition to the requested amount of bytes. */
		if( xWantedSize > 0 )
		{
			xWantedSize += xHeapStructSize;

			/* Ensure that blocks are always aligned to the required number of
			 * bytes. */
			if( ( xWantedSize & secureportBYTE_ALIGNMENT_MASK ) != 0x00 )
			{
				/* Byte alignment required. */
				xWantedSize += ( secureportBYTE_ALIGNMENT - ( xWantedSize & secureportBYTE_ALIGNMENT_MASK ) );
				secureportASSERT( ( xWantedSize & secureportBYTE_ALIGNMENT_MASK ) == 0 );
			}
			else
			{
				mtCOVERAGE_TEST_MARKER();
			}
		}
		else
		{
			mtCOVERAGE_TEST_MARKER();
		}

		if( ( xWantedSize > 0 ) && ( xWantedSize <= xFreeBytesRemaining ) )
		{
			/* Traverse the list from the start (lowest address) block until
			 * one of adequate size is found. */
			pxPreviousBlock = &xStart;
			pxBlock = xStart.pxNextFreeBlock;
			while( ( pxBlock->xBlockSize < xWantedSize ) && ( pxBlock->pxNextFreeBlock != NULL ) )
			{
				pxPreviousBlock = pxBlock;
				pxBlock = pxBlock->pxNextFreeBlock;
			}

			/* If the end marker was reached then a block of adequate size was
			 * not found. */
			if( pxBlock != pxEnd )
			{
				/* Return the memory space pointed to - jumping over the
				 * BlockLink_t structure at its start. */
				pvReturn = ( void * ) ( ( ( uint8_t * ) pxPreviousBlock->pxNextFreeBlock ) + xHeapStructSize );

				/* This block is being returned for use so must be taken out
				 * of the list of free blocks. */
				pxPreviousBlock->pxNextFreeBlock = pxBlock->pxNextFreeBlock;

				/* If the block is larger than required it can be split into
				 * two. */
				if( ( pxBlock->xBlockSize - xWantedSize ) > secureheapMINIMUM_BLOCK_SIZE )
				{
					/* This block is to be split into two.  Create a new
					 * block following the number of bytes requested. The void
					 * cast is used to prevent byte alignment warnings from the
					 * compiler. */
					pxNewBlockLink = ( void * ) ( ( ( uint8_t * ) pxBlock ) + xWantedSize );
					secureportASSERT( ( ( ( size_t ) pxNewBlockLink ) & secureportBYTE_ALIGNMENT_MASK ) == 0 );

					/* Calculate the sizes of two blocks split from the single
					 * block. */
					pxNewBlockLink->xBlockSize = pxBlock->xBlockSize - xWantedSize;
					pxBlock->xBlockSize = xWantedSize;

					/* Insert the new block into the list of free blocks. */
					prvInsertBlockIntoFreeList( pxNewBlockLink );
				}
				else
				{
					mtCOVERAGE_TEST_MARKER();
				}

				xFreeBytesRemaining -= pxBlock->xBlockSize;

				if( xFreeBytesRemaining < xMinimumEverFreeBytesRemaining )
				{
					xMinimumEverFreeBytesRemaining = xFreeBytesRemaining;
				}
				else
				{
					mtCOVERAGE_TEST_MARKER();
				}

				/* The block is being returned - it is allocated and owned by
				 * the application and has no "next" block. */
				pxBlock->xBlockSize |= xBlockAllocatedBit;
				pxBlock->pxNextFreeBlock = NULL;
			}
			else
			{
				mtCOVERAGE_TEST_MARKER();
			}
		}
		else
		{
			mtCOVERAGE_TEST_MARKER();
		}
	}
	else
	{
		mtCOVERAGE_TEST_MARKER();
	}

	traceMALLOC( pvReturn, xWantedSize );

	#if( secureconfigUSE_MALLOC_FAILED_HOOK == 1 )
	{
		if( pvReturn == NULL )
		{
			extern void vApplicationMallocFailedHook( void );
			vApplicationMallocFailedHook();
		}
		else
		{
			mtCOVERAGE_TEST_MARKER();
		}
	}
	#endif

	secureportASSERT( ( ( ( size_t ) pvReturn ) & ( size_t ) secureportBYTE_ALIGNMENT_MASK ) == 0 );
	return pvReturn;
}
/*-----------------------------------------------------------*/

void vPortFree( void *pv )
{
uint8_t *puc = ( uint8_t * ) pv;
BlockLink_t *pxLink;

	if( pv != NULL )
	{
		/* The memory being freed will have an BlockLink_t structure immediately
		 * before it. */
		puc -= xHeapStructSize;

		/* This casting is to keep the compiler from issuing warnings. */
		pxLink = ( void * ) puc;

		/* Check the block is actually allocated. */
		secureportASSERT( ( pxLink->xBlockSize & xBlockAllocatedBit ) != 0 );
		secureportASSERT( pxLink->pxNextFreeBlock == NULL );

		if( ( pxLink->xBlockSize & xBlockAllocatedBit ) != 0 )
		{
			if( pxLink->pxNextFreeBlock == NULL )
			{
				/* The block is being returned to the heap - it is no longer
				 * allocated. */
				pxLink->xBlockSize &= ~xBlockAllocatedBit;

				secureportDISABLE_NON_SECURE_INTERRUPTS();
				{
					/* Add this block to the list of free blocks. */
					xFreeBytesRemaining += pxLink->xBlockSize;
					traceFREE( pv, pxLink->xBlockSize );
					prvInsertBlockIntoFreeList( ( ( BlockLink_t * ) pxLink ) );
				}
				secureportENABLE_NON_SECURE_INTERRUPTS();
			}
			else
			{
				mtCOVERAGE_TEST_MARKER();
			}
		}
		else
		{
			mtCOVERAGE_TEST_MARKER();
		}
	}
}
/*-----------------------------------------------------------*/

size_t xPortGetFreeHeapSize( void )
{
	return xFreeBytesRemaining;
}
/*-----------------------------------------------------------*/

size_t xPortGetMinimumEverFreeHeapSize( void )
{
	return xMinimumEverFreeBytesRemaining;
}
/*-----------------------------------------------------------*/

void vPortInitialiseBlocks( void )
{
	/* This just exists to keep the linker quiet. */
}
/*-----------------------------------------------------------*/
