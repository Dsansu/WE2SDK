/*
 * spi_protocol.h
 *
 *  Created on: 2020�~5��7��
 *      Author: 902449
 */

#ifndef INC_SPI_PROTOCOL_H_
#define INC_SPI_PROTOCOL_H_

/**
 * @brief defined protocol format
 * -------------header---------------- -------------data---------------
 * || ID number| data type| data size| | user-defined info| raw data ||
 * || 2 bytes  | 1 bytes  | 4 bytes  | | max 17 bytes     | max 976KB||
 * --------------------------------------------------------------------
 */

#define PTL_HEADER_LEN (7)
#define MAX_TRACKED_ALGO_RES  10
#define MAX_FACE_LAND_MARK_TRACKED_POINT 68
#define HUMAN_POSE_POINT_NUM  17
#define FACE_MESH_POINT_NUM 468
#define FACE_MESH_EYE_UPDATE_POINT_NUM 142
#define FACE_MESH_IRIS_POINT_NUM 10
#define HAND_LANDMARK_POINT_NUM 21
#define ENROLL_PEOPLE_NUM 5
#define ENROLL_PEOPLE_NAME_LEN 15
#define MAX_TRACKED_YOLOV8_ALGO_RES 40
typedef enum
{
	DATA_TYPE_JPG               = 0x01,
	DATA_TYPE_BMP               = 0x02,
	DATA_TYPE_VO_CMD            = 0x03,
	DATA_TYPE_HUNN_PRESENT      = 0x04,
	DATA_TYPE_WKUP_METHOD       = 0x05,
	DATA_TYPE_HUMN_LV_TIMEOUT   = 0x06,
	DATA_TYPE_LANGUAGE          = 0x07,
#ifdef TV01
	DATA_TYPE_HUNN_LOCK_COUNT   = 0x08,
	DATA_TYPE_EYE_PROT_TIMEOUT  = 0x09,
#endif
    DATA_TYPE_VOICE_TIMEOUT     = 0x0A,
	DATA_TYPE_DBG_MSG           = 0x10,
	DATA_TYPE_WARN_MSG          = 0x11,
	DATA_TYPE_CTRL_MSG          = 0x12,
	DATA_TYPE_META_DATA         = 0x13,
	DATA_TYPE_JPG_L             = 0x14,
	DATA_TYPE_JPG_R             = 0x15,
	DATA_TYPE_RAW_IMG           = 0x16,
	DATA_TYPE_BIN_DATA          = 0x20,
	DATA_TYPE_INCORRECT_DATA    = 0x3F,
    DATA_TYPE_TV_STANDBY        = 0x40,

	DATA_TYPE_AREA_SUMMARY      = 0x5A,
	DATA_TYPE_AREA_DETAIL       = 0x5C,

	DATA_TYPE_QRCODE_RESULT     = 0x60,
	DATA_TYPE_WR_CONFIG         = 0x61,
	DATA_TYPE_SENSOR_REG    	= 0x62,
	
	DATA_TYPE_RAW_HEADER_IMG_MONO   = 0x70,
    DATA_TYPE_RAW_HEADER_IMG_BGR    = 0x71,
    DATA_TYPE_RAW_HEADER_IMG_YUV422_8U3C = 0x72,
    DATA_TYPE_RAW_HEADER_IMG_YUV420_8U3C = 0x73,
	DATA_TYPE_RAW_HEADER_IMG_BAYER = 0x74,
    DATA_TYPE_RAW_HEADER_IMG_YUYV = 0x75,
    DATA_TYPE_RAW_HEADER_IMG_RGB565 = 0x76,
    DATA_TYPE_RAW_HEADER_IMG_RGB555 = 0x77,
    DATA_TYPE_RAW_HEADER_IMG_RGB444 = 0x78,
    DATA_TYPE_RAW_HEADER_IMG_GBR    = 0x79,
	DATA_TYPE_RAW_HEADER_IMG_YVYU = 0x7A,
	DATA_TYPE_RAW_HEADER_IMG_UYVY = 0x7B,
	DATA_TYPE_RAW_HEADER_IMG_VYUY = 0x7C,
	DATA_TYPE_RAW_HEADER_IMG_BGR565 = 0x7D,
	DATA_TYPE_RAW_HEADER_IMG_BGR555 = 0x7E,
	DATA_TYPE_RAW_HEADER_IMG_BGR444 = 0x7F,
	DATA_TYPE_RAW_HEADER_IMG_RGB_1PIX  = 0x80,
    DATA_TYPE_RAW_HEADER_IMG_BGR_1PIX = 0x81,
	DATA_TYPE_RAW_HEADER_IMG_BAYER_RG = 0x82,
	DATA_TYPE_RAW_HEADER_IMG_BAYER_GB = 0x83,
	DATA_TYPE_RAW_HEADER_IMG_BAYER_GR = 0x84,

	DATA_TYPE_PDM				= 0x90,
	DATA_TYPE_ALANGO			= 0x91,

	DATA_TYPE_META_FL_DATA = 0X92, /*FACE LANDMARK POINT*/
    
	DATA_TYPE_META_HP_DATA = 0X94, /*HUMAN POSE POINT*/
	
	DATA_TYPE_META_FM_DATA = 0X95, /*face mesh POINT*/

	DATA_TYPE_META_HP_HL_DATA = 0X96, /*human pose and hand landmark*/

	DATA_TYPE_META_HL_DATA = 0X97, /*only hand landmark point*/

	DATA_TYPE_META_FL_FR_DATA = 0X98, /*FACE LANDMARK and face recogntion*/

	DATA_TYPE_META_FL_FR_ENROLL_DATA = 0X99, /*FACE LANDMARK and face recogntion ENROLL MODE*/

	DATA_TYPE_META_YOLOV8_OB_DATA = 0X9A, /*YOLOV8 object detection*/

	DATA_TYPE_META_YOLOFASTEST_OB_DATA = 0X9B, /*YOLOFASTEST object detection*/

	DATA_TYPE_END_OF_PACKET = 0XF0, /*represent end of data*/

}SPI_CMD_DATA_TYPE;

typedef struct
{
	uint32_t x;
	uint32_t y;
	uint32_t width;
	uint32_t height;
}struct__box;

typedef struct
{
	struct__box bbox;
	uint32_t time_of_existence;
	uint32_t is_reliable;
}struct_MotionTarget;

typedef struct {
	uint32_t x;
	uint32_t y;
}struct_position;

typedef struct {
    int16_t x;
    int16_t y;
}struct_position_int16;

typedef struct {
	float yaw;
	float pitch;
	float roll;
	float MAR;
	float REAR;
	float LEAR;
}struct_angle;

typedef struct
{
	struct__box upper_body_bbox;
	uint32_t upper_body_scale;
	uint32_t upper_body_score;
	uint32_t upper_body_num_frames_since_last_redetection_attempt;
	struct__box head_bbox;
	uint32_t head_scale;
	uint32_t head_score;
	uint32_t head_num_frames_since_last_redetection_attempt;
	struct_position face_landmark[MAX_FACE_LAND_MARK_TRACKED_POINT];
	struct_angle face_angle;
	struct_position_int16 left_eye_landmark[9];
	struct_position_int16 right_eye_landmark[9];
	float left_eye_theta;
	float left_eye_phi;
	float right_eye_theta;
	float right_eye_phi;
	uint32_t octave;
	uint32_t time_of_existence;
	uint32_t isVerified;
}struct_Human;

typedef struct
{
	int num_hot_pixels ;
	struct_MotionTarget Emt[MAX_TRACKED_ALGO_RES];  //ecv::motion::Target* *tracked_moving_targets;
	int frame_count ;
	short num_tracked_moving_targets;
	short num_tracked_human_targets ;
	bool humanPresence ;
	struct_Human ht[MAX_TRACKED_ALGO_RES];  //TrackedHumanTarget* *tracked_human_targets;
	int num_reliable_moving_targets;
	int verifiedHumansExist;
}struct_algoResult;


/**for human pose inference**/
typedef struct struct_human_pose{
    uint32_t x;
    uint32_t y;
    float score;
} struct_human_pose;

typedef struct
{
	struct__box bbox;
    struct_human_pose hpr[HUMAN_POSE_POINT_NUM];
}struct_hp_algoResult;

/**for face mesh inference**/
typedef struct struct_face_mesh{
    int16_t x;
    int16_t y;
    // int16_t z;
} struct_face_mesh;


typedef struct
{
	uint16_t x;
	uint16_t y;
	uint16_t width;
	uint16_t height;
	uint16_t face_score;
}struct_face_box;

typedef struct
{
	short num_tracked_face_targets ;
	struct_face_box face_bbox[MAX_TRACKED_ALGO_RES];
	float score;
    struct_face_mesh fmr[FACE_MESH_POINT_NUM];
	//struct_face_mesh fmr_eye_update[FACE_MESH_EYE_UPDATE_POINT_NUM];
	struct_face_mesh fmr_iris[FACE_MESH_IRIS_POINT_NUM];
	float left_iris_theta;
	float left_iris_phi;
	float right_iris_theta;
	float right_iris_phi;
	struct_angle face_angle;

}struct_fm_algoResult;




typedef struct struct_hand_landmark{
    int16_t x[HAND_LANDMARK_POINT_NUM];
    int16_t y[HAND_LANDMARK_POINT_NUM];
    float present_score;
	float left_right_score;
	struct__box bbox;
} struct_hand_landmark;
typedef struct
{
	struct_hand_landmark left_hand;
	struct_hand_landmark right_hand;
	struct__box bbox;
    struct_human_pose hpr[HUMAN_POSE_POINT_NUM];
}struct_hp_hl_algoResult;


typedef struct struct_lrnet_hand_landmark{
    int16_t x[HAND_LANDMARK_POINT_NUM];
    int16_t y[HAND_LANDMARK_POINT_NUM];
    float present_score[HAND_LANDMARK_POINT_NUM];
	struct__box bbox;
} struct_lrnet_hand_landmark;

typedef struct
{
	struct_lrnet_hand_landmark handlandmark;
}struct_hl_algoResult;



/***FACE LANDMARK and face recogntion**/

typedef struct
{
	struct__box upper_body_bbox;
	uint32_t upper_body_scale;
	uint32_t upper_body_score;
	struct_position face_landmark[MAX_FACE_LAND_MARK_TRACKED_POINT];
	struct_angle face_angle;
	struct_position_int16 left_eye_landmark[9];
	struct_position_int16 right_eye_landmark[9];
	float left_eye_theta;
	float left_eye_phi;
	float right_eye_theta;
	float right_eye_phi;
	uint32_t isVerified;
	bool fr_id_pass[ENROLL_PEOPLE_NUM];
}struct_Human_fl_fr;

typedef struct
{
	short num_tracked_human_targets ;
	struct_Human_fl_fr ht[MAX_TRACKED_ALGO_RES];  //TrackedHumanTarget* *tracked_human_targets;
	char fr_name[ENROLL_PEOPLE_NUM][ENROLL_PEOPLE_NAME_LEN];
}struct_fl_fr_algoResult;



typedef struct
{
	short num_tracked_human_targets ;
	struct_Human_fl_fr ht[MAX_TRACKED_ALGO_RES];  //TrackedHumanTarget* *tracked_human_targets;
	char fr_name[ENROLL_PEOPLE_NUM][ENROLL_PEOPLE_NAME_LEN];
	int16_t enroll_id;
	bool enroll_dir_status[ENROLL_PEOPLE_NUM][5];//enroll direction= straight up down left right
	int16_t enroll_name_done_flag;
}struct_fl_fr_enroll_algoResult;

/***FACE LANDMARK and face recogntion**/



typedef struct
{
	struct__box bbox;
	float confidence;
    uint16_t class_idx;
}struct_yolov8_ob;

typedef struct
{
	struct_yolov8_ob obr[MAX_TRACKED_YOLOV8_ALGO_RES];
}struct_yolov8_ob_algoResult;


#endif /* INC_SPI_PROTOCOL_H_ */
