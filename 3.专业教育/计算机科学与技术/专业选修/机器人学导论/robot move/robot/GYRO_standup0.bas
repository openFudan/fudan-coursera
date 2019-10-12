
DIM tilt_CNT AS BYTE
DIM grip_pose AS BYTE
DIM Action_mode AS BYTE

DIM motorONOFF AS BYTE'把I定义成字节型
DIM I AS BYTE'把I定义成字节型
DIM J AS BYTE'把J定义成字节型
DIM pose AS BYTE

DIM A AS BYTE
DIM A_old AS BYTE
DIM B AS BYTE


'**** tilt_port *****

CONST FB_tilt_AD_port = 2'前后倾斜地址 点
CONST LR_tilt_AD_port = 3'左右倾斜地址 点

'**** 2012 NEW tilt Sensors *****‘2012新的倾斜传感器
CONST tilt_time_check = 5  '倾斜时间检查
CONST min = 61			'最小值
CONST max = 107			'最大值
CONST COUNT_MAX = 20'计算
'*******************


PTP SETON 				
PTP ALLON				

DIR G6A,1,0,0,1,0,0		'motor0~5
DIR G6B,1,1,1,1,1,1		'motor6~11
DIR G6C,0,0,0,0,0,0		'motor12~17
DIR G6D,0,1,1,0,1,0		'motor18~23

'**** Feedback *****************************
'**** Feedback *****************************

GOSUB MOTOR_ON

SPEED 5
GOSUB power_first_pose
GOSUB stand_pose


GOTO MAIN




MOTOR_ON:

    GOSUB MOTOR_GET

    MOTOR G6B
    DELAY 50
    MOTOR G6C
    DELAY 50
    MOTOR G6A
    DELAY 50
    MOTOR G6D

    motorONOFF = 0
    'GOSUB start_music			
    RETURN
power_first_pose:
    MOVE G6A,95,  76, 145,  93, 105, 100
    MOVE G6D,95,  76, 145,  93, 105, 100
    MOVE G6B,100,  45,  90, 100, 100, 100
    MOVE G6C,100,  45,  90, 100, 100, 100
    WAIT
    pose = 0
    RETURN

    '************************************************
MOTOR_GET:
    GETMOTORSET G6A,1,1,1,1,1,0
    GETMOTORSET G6B,1,1,1,0,0,0
    GETMOTORSET G6C,1,1,1,0,0,0
    GETMOTORSET G6D,1,1,1,1,1,0
    RETURN


    '******************************************	
MAIN: 'WAIT

			'备份1
	MOVE G6A, 100,  81, 131, 103, 106,  
	MOVE G6D, 100,  81, 131, 103, 106,  
	MOVE G6B,  97,  41,  82,  ,  ,  
	MOVE G6C,  97,  41,  82,  ,  ,  

	DELAY 500
	
	'鬼畜转圈-左
	
	FOR i = 1 TO 35
	
		SPEED 5
    	MOVE G6A,97,  86, 145,  82, 103, 100
    	MOVE G6D,97,  66, 145,  102, 103, 100 
    	MOVE G6B,  97,  31,  82,  ,  ,  
		MOVE G6C,  97,  31,  82,  ,  ,  
    	WAIT

    	SPEED 10
    	MOVE G6A,94,  86, 145,  82, 101, 100
    	MOVE G6D,94,  66, 145,  102, 101, 100
    	MOVE G6B,  97,  41,  82,  ,  ,  
		MOVE G6C,  97,  41,  82,  ,  ,  
   		WAIT

    	SPEED 5
    	MOVE G6A,101,  76, 146,  92, 98, 100
    	MOVE G6D,101,  76, 146,  92, 98, 100
    	MOVE G6B,  97,  31,  82,  ,  ,  
		MOVE G6C,  97,  31,  82,  ,  ,  
   		WAIT

    	MOVE G6A,100,  76, 145,  92, 100
    	MOVE G6D,100,  76, 145,  92, 100
    	MOVE G6B,  97,  41,  82,  ,  ,  
		MOVE G6C,  97,  41,  82,  ,  ,  
    	WAIT
    	
    NEXT i
    	
    DELAY 200


	
	'左伸腿
	
	SPEED 12
	
	MOVE G6A,  93,  76, 145,  93, 107,  	   '1  手平
	MOVE G6D,  93,  76, 145,  93, 107,  
	MOVE G6B, 145,  81,  88,  ,  ,  
	MOVE G6C, 145,  81,  88,  ,  ,  
	
	MOVE G6A,  96, 104,  80, 133, 100,  
	MOVE G6D,  98, 108,  74, 131, 107,     
	MOVE G6B, 185, 172, 160,  ,  ,  
	MOVE G6C, 184,  24,  31,  ,  ,  
	
	MOVE G6A,  96, 127,  55, 131, 103,  
	MOVE G6D,  95, 132,  49, 127, 107,    
	MOVE G6B, 187,  14,  44,  ,  ,  
	MOVE G6C, 189, 173, 162,  ,  ,  
	
	
	MOVE G6A,  96, 143,  26, 148, 108,  		
	MOVE G6D,  96, 143,  26, 148, 108,  
	MOVE G6B, 185, 172, 160,  ,  ,  
	MOVE G6C, 184,  24,  31,  ,  , 
	
	MOVE G6A,  97, 160,  22, 127, 102,  		'全蹲
	MOVE G6D, 102, 164,  25, 123,  99,  
	MOVE G6B, 187,  14,  44,  ,  ,  
	MOVE G6C, 189, 173, 162,  ,  ,  
	
	
	MOVE G6A,  59,  89, 115, 106, 118,  		'伸腿
	MOVE G6D, 107, 150,  25, 135, 114, 
	MOVE G6B, 185, 172, 160,  ,  ,  
	MOVE G6C, 184,  24,  31,  ,  , 
	
	MOVE G6A,  73, 140,  28, 139, 125,  
	MOVE G6D,  79, 157,  21, 129, 122,  
	MOVE G6B, 187,  14,  44,  ,  ,  
	MOVE G6C, 189, 173, 162,  ,  , 
	
	MOVE G6A, 100,  81, 131, 103, 106,  
	MOVE G6D, 100,  81, 131, 103, 106,  
	MOVE G6B,  97,  41,  82,  ,  ,  
	MOVE G6C,  97,  41,  82,  ,  , 
	
	
	'手臂波浪+身体摇动
	
	SPEED 8
	
	MOVE G6A, 109,  76, 145,  93,  85,  
	MOVE G6D,  87,  76, 145,  93, 119,  
	MOVE G6B, 105,  50, 189,  ,  ,  
	MOVE G6C, 100, 150,  11,  ,  ,  
	
	MOVE G6A,  85,  76, 145,  93, 118,  
	MOVE G6D, 108,  76, 145,  93,  88,  
	MOVE G6B, 106, 155,  13,  ,  ,  
	MOVE G6C,  99,  68, 188,  ,  ,
	
	SPEED 11
	
	MOVE G6A, 109,  76, 145,  93,  85,  
	MOVE G6D,  87,  76, 145,  93, 119,  
	MOVE G6B, 105,  50, 189,  ,  ,  
	MOVE G6C, 100, 150,  11,  ,  ,  
	
	MOVE G6A,  85,  76, 145,  93, 118,  
	MOVE G6D, 108,  76, 145,  93,  88,  
	MOVE G6B, 106, 155,  13,  ,  ,  
	MOVE G6C,  99,  68, 188,  ,  ,
	
	MOVE G6A, 109,  76, 145,  93,  85,  
	MOVE G6D,  87,  76, 145,  93, 119,  
	MOVE G6B, 105,  50, 189,  ,  ,  
	MOVE G6C, 100, 150,  11,  ,  ,  
	
	MOVE G6A,  85,  76, 145,  93, 118,  
	MOVE G6D, 108,  76, 145,  93,  88,  
	MOVE G6B, 106, 155,  13,  ,  ,  
	MOVE G6C,  99,  68, 188,  ,  ,
	
	MOVE G6A, 109,  76, 145,  93,  85,  
	MOVE G6D,  87,  76, 145,  93, 119,  
	MOVE G6B, 105,  50, 189,  ,  ,  
	MOVE G6C, 100, 150,  11,  ,  ,  
	
	MOVE G6A,  85,  76, 145,  93, 118,  
	MOVE G6D, 108,  76, 145,  93,  88,  
	MOVE G6B, 106, 155,  13,  ,  ,  
	MOVE G6C,  99,  68, 188,  ,  ,
	
	MOVE G6A, 109,  76, 145,  93,  85,  
	MOVE G6D,  87,  76, 145,  93, 119,  
	MOVE G6B, 105,  50, 189,  ,  ,  
	MOVE G6C, 100, 150,  11,  ,  ,  
	
	MOVE G6A,  85,  76, 145,  93, 118,  
	MOVE G6D, 108,  76, 145,  93,  88,  
	MOVE G6B, 106, 155,  13,  ,  ,  
	MOVE G6C,  99,  68, 188,  ,  ,
	
	
	
	'右伸腿
	
	SPEED 12
	
	MOVE G6D,  93,  76, 145,  93, 107,  		'1  手平
	MOVE G6A,  93,  76, 145,  93, 107,  
	MOVE G6B, 145,  81,  88,  ,  ,  
	MOVE G6C, 145,  81,  88,  ,  ,  
	
	MOVE G6D,  96, 104,  80, 133, 100,  
	MOVE G6A,  98, 108,  74, 131, 107,     
	MOVE G6B, 185, 172, 160,  ,  ,  
	MOVE G6C, 184,  24,  31,  ,  ,  
	
	MOVE G6D,  96, 127,  55, 131, 103,  
	MOVE G6A,  95, 132,  49, 127, 107,    
	MOVE G6B, 187,  14,  44,  ,  ,  
	MOVE G6C, 189, 173, 162,  ,  ,  
	
	MOVE G6D,  96, 143,  26, 148, 108,  		
	MOVE G6A,  96, 143,  26, 148, 108,  
	MOVE G6B, 185, 172, 160,  ,  ,  
	MOVE G6C, 184,  24,  31,  ,  , 
	
	MOVE G6D,  97, 160,  22, 127, 102,  		'全蹲
	MOVE G6A, 102, 164,  25, 123,  99,  
	MOVE G6B, 187,  14,  44,  ,  ,  
	MOVE G6C, 189, 173, 162,  ,  ,  
	
	MOVE G6D,  59,  89, 115, 106, 118,  		'伸腿
	MOVE G6A, 107, 150,  25, 135, 114, 
	MOVE G6B, 185, 172, 160,  ,  ,  
	MOVE G6C, 184,  24,  31,  ,  , 
	
	MOVE G6D,  73, 140,  28, 139, 125,  
	MOVE G6A,  79, 157,  21, 129, 122,  
	MOVE G6B, 187,  14,  44,  ,  ,  
	MOVE G6C, 189, 173, 162,  ,  , 
	
	MOVE G6A, 100,  81, 131, 103, 106,  
	MOVE G6D, 100,  81, 131, 103, 106,  
	MOVE G6B,  97,  41,  82,  ,  ,  
	MOVE G6C,  97,  41,  82,  ,  ,
	
	
	DELAY 1000
	
	 '左横走
	
	FOR i = 1 TO 3 

		SPEED 2
	    MOVE G6A, 88,  71, 152,  91, 110, 
	    MOVE G6D,108,  76, 146,  93,  92, 
	    MOVE G6B,100,  40,  80
	    MOVE G6C,100,  40,  80
	    WAIT
	
	    SPEED 2
	    MOVE G6A, 85,  80, 140, 95, 114, 100
	    MOVE G6D,112,  76, 146,  93, 98, 100
	    MOVE G6B,100,  40,  80
	    MOVE G6C,100,  40,  80
	    WAIT
	
	
	    SPEED 3
	    MOVE G6D,110,  92, 124,  97,  93,  100
	    MOVE G6A, 76,  72, 160,  82, 128,  100
	    MOVE G6B,100,  40,  80, , , ,
	    MOVE G6C,100,  40,  80, , , ,
	    WAIT
	
	    SPEED 3
	    MOVE G6A,94,  76, 145,  93, 106, 100
	    MOVE G6D,94,  76, 145,  93, 106, 100
	    MOVE G6B,100,  40,  80
	    MOVE G6C,100,  40,  80
	    WAIT	
	    
	    SPEED 3
	    MOVE G6A,110,  92, 124,  97,  93,  100
	    MOVE G6D, 76,  72, 160,  82, 120,  100
	    MOVE G6B,100,  40,  80, , , ,
	    MOVE G6C,100,  40,  80, , , ,
	    WAIT
	
	    SPEED 4
	    MOVE G6D, 85,  80, 140, 95, 110, 100
	    MOVE G6A,112,  76, 146,  93, 98, 100
	    MOVE G6B,100,  40,  80
	    MOVE G6C,100,  40,  80
	    WAIT
	
	    SPEED 2
	    MOVE G6D, 88,  71, 152,  91, 110, 
	    MOVE G6A,108,  76, 146,  93,  92, 
	    MOVE G6B,100,  40,  80
	    MOVE G6C,100,  40,  80
	    WAIT
	    
	NEXT i
    
    DELAY 1000
    
    '右劈叉
    
    SPEED 10

	MOVE G6A, 101,  77, 143,  89, 186,  10
	MOVE G6D, 101,  77, 143,  89, 186,  10
	MOVE G6B, 185, 172, 160,  ,  ,  
	MOVE G6C, 184,  24,  31,  ,  , 
	WAIT
	
	SPEED 8
	
	MOVE G6A,  44, 157,  29, 130, 189,  170
	MOVE G6D,  44, 123,  27, 160, 186,  170
	MOVE G6B, 187,  14,  44,  ,  ,  
	MOVE G6C, 189, 173, 162,  ,  ,  
	WAIT

	MOVE G6A,  85, 158,  29, 132, 111, 60 
	MOVE G6D,  81, 150,  27, 141, 122,  60
	MOVE G6B, 185, 172, 160,  ,  ,  
	MOVE G6C, 184,  24,  31,  ,  ,
	WAIT

	MOVE G6A, 100,  76, 145,  93, 100, 20  
	MOVE G6D, 100,  76, 145,  93, 100, 20
	MOVE G6B, 187,  14,  44,  ,  ,  
	MOVE G6C, 189, 173, 162,  ,  ,  
	WAIT
    
    SPEED 10
    
    MOVE G6A, 100,  81, 131, 103, 106,  
	MOVE G6D, 100,  81, 131, 103, 106,  
	MOVE G6B,  97,  41,  82,  ,  ,  
	MOVE G6C,  97,  41,  82,  ,  , 
	WAIT
	
	
	'右横走
	
	FOR i = 1 TO 3 

		SPEED 2
	    MOVE G6D, 88,  71, 152,  91, 110, 
	    MOVE G6A,108,  76, 146,  93,  92, 
	    MOVE G6B,100,  40,  80
	    MOVE G6C,100,  40,  80
	    WAIT
	
	    SPEED 2
	    MOVE G6D, 85,  80, 140, 95, 114, 100
	    MOVE G6A,112,  76, 146,  93, 98, 100
	    MOVE G6B,100,  40,  80
	    MOVE G6C,100,  40,  80
	    WAIT
	
	
	    SPEED 3
	    MOVE G6A,110,  92, 124,  97,  93,  100
	    MOVE G6D, 76,  72, 160,  82, 128,  100
	    MOVE G6B,100,  40,  80, , , ,
	    MOVE G6C,100,  40,  80, , , ,
	    WAIT
	
	    SPEED 3
	    MOVE G6D,94,  76, 145,  93, 106, 100
	    MOVE G6A,94,  76, 145,  93, 106, 100
	    MOVE G6B,100,  40,  80
	    MOVE G6C,100,  40,  80
	    WAIT	
	    
	    SPEED 3
	    MOVE G6D,110,  92, 124,  97,  93,  100
	    MOVE G6A, 76,  72, 160,  82, 120,  100
	    MOVE G6B,100,  40,  80, , , ,
	    MOVE G6C,100,  40,  80, , , ,
	    WAIT
	
	    SPEED 4
	    MOVE G6A, 85,  80, 140, 95, 110, 100
	    MOVE G6D,112,  76, 146,  93, 98, 100
	    MOVE G6B,100,  40,  80
	    MOVE G6C,100,  40,  80
	    WAIT
	
	    SPEED 2
	    MOVE G6A, 88,  71, 152,  91, 110, 
	    MOVE G6D,108,  76, 146,  93,  92, 
	    MOVE G6B,100,  40,  80
	    MOVE G6C,100,  40,  80
	    WAIT
	    
	NEXT i
    
    DELAY 1000
    
    '左劈叉
    
    SPEED 10

	MOVE G6D, 101,  77, 143,  89, 186,  10
	MOVE G6A, 101,  77, 143,  89, 186,  10
	MOVE G6C, 185, 172, 160,  ,  ,  
	MOVE G6B, 184,  24,  31,  ,  , 
	WAIT
	
	SPEED 8
	
	MOVE G6D,  44, 157,  29, 130, 189,  170
	MOVE G6A,  44, 123,  27, 160, 186,  170
	MOVE G6C, 187,  14,  44,  ,  ,  
	MOVE G6B, 189, 173, 162,  ,  ,  
	WAIT

	MOVE G6D,  85, 158,  29, 132, 111, 60 
	MOVE G6A,  81, 150,  27, 141, 122,  60
	MOVE G6C, 185, 172, 160,  ,  ,  
	MOVE G6B, 184,  24,  31,  ,  ,
	WAIT

	MOVE G6D, 100,  76, 145,  93, 100, 20  
	MOVE G6A, 100,  76, 145,  93, 100, 20
	MOVE G6C, 187,  14,  44,  ,  ,  
	MOVE G6B, 189, 173, 162,  ,  ,  
	WAIT
    
    SPEED 10
    
    MOVE G6A, 100,  81, 131, 103, 106,  
	MOVE G6D, 100,  81, 131, 103, 106,  
	MOVE G6B,  97,  41,  82,  ,  ,  
	MOVE G6C,  97,  41,  82,  ,  , 
	WAIT
	
	DELAY 1000
	
	
	
	FOR i = 1 TO 3
	
		'左大踏步
		
		SPEED 8
	    MOVE G6A, 88,  71, 152,  86, 110,
	    MOVE G6D,108,  76, 146,  88,  92, 
	    MOVE G6B,189,  47,  13,  ,  , 
	    MOVE G6C,187,  59,  83,  ,  ,  
	    WAIT
	
	    SPEED 4
	    MOVE G6A, 85,  80, 140, 90, 114,
	    MOVE G6D,112,  76, 146,  88, 98,
	    MOVE G6B,189,  47,  13,  ,  , 
	    MOVE G6C,187,  59,  83,  ,  ,  
	    WAIT
	
	    SPEED 6
	
	    MOVE G6A,95,  84, 105, 121,  105,
	    MOVE G6D, 86, 110, 136,  64, 114,
	    MOVE G6B,189,  47,  13,  ,  , 
	    MOVE G6C,187,  59,  83,  ,  ,   
	    WAIT
	
	    DELAY 100
	
		SPEED 8
	    MOVE G6A,93,  80, 130, 105,  105,
	    MOVE G6D, 93, 80, 130,  105, 105,
	    MOVE G6B,189,  47,  13,  ,  , 
	    MOVE G6C,187,  59,  83,  ,  ,   
	    WAIT
	
	    SPEED 4
	    MOVE G6A,101,  80, 130, 105,  98,
	    MOVE G6D, 101, 80, 130,  105, 98,
	    MOVE G6B,189,  47,  13,  ,  , 
	    MOVE G6C,187,  59,  83,  ,  ,   
	    WAIT
	    
	    
	    '右大踏步
	    
	    SPEED 8
	    MOVE G6A,108,  76, 146,  88,  92
	    MOVE G6D, 88,  71, 152,  86, 110
	    MOVE G6B, 187,  59,  83,  ,  ,  
		MOVE G6C, 189,  47,  13,  ,  , 
	    WAIT
	
	    SPEED 4
	    MOVE G6A,112,  76, 146,  88, 98
	    MOVE G6D, 85,  80, 140, 90, 114
	    MOVE G6B, 187,  59,  83,  ,  ,  
		MOVE G6C, 189,  47,  13,  ,  ,  
	    WAIT
	    SPEED 6
	
		MOVE G6A, 86, 110, 136,  64, 114,
	    MOVE G6D,95,  84, 105, 121,  105,
	    MOVE G6B, 187,  59,  83,  ,  ,  
		MOVE G6C, 189,  47,  13,  ,  ,  
	    WAIT
	
	    DELAY 100
	    
	    SPEED 8
	    MOVE G6A, 93, 80, 130,  105, 105,
	    MOVE G6D,93,  80, 130, 105,  105,
	    MOVE G6B, 187,  59,  83,  ,  ,  
		MOVE G6C, 189,  47,  13,  ,  ,  
	    WAIT
	
	    SPEED 4
	    MOVE G6A, 101, 80, 130,  105, 98,
	    MOVE G6D,101,  80, 130, 105,  98,
	    MOVE G6B, 187,  59,  83,  ,  ,  
		MOVE G6C, 189,  47,  13,  ,  , 
	    WAIT
    
    NEXT i
    
    
    MOVE G6A, 100,  81, 131, 103, 106,  
	MOVE G6D, 100,  81, 131, 103, 106,  
	MOVE G6B,  97,  41,  82,  ,  ,  
	MOVE G6C,  97,  41,  82,  ,  ,  
	
	DELAY 500
    
    
    '后倒俯卧
	SPEED 5
	
	MOVE G6A,  93, 163,  26, 127, 109,  
	MOVE G6D,  95, 165,  21, 128, 110,  
	MOVE G6B,  12,  36,  88,  ,  ,  
	MOVE G6C,  12,  36,  88,  ,  ,  
	
	MOVE G6A,  94, 149,  25,  80, 106,  
	MOVE G6D,  96, 164,  21,  65, 109,  
	MOVE G6B,  11,  37,  88,  ,  ,  
	MOVE G6C,  12,  36,  88,  ,  ,  
	
	DELAY 800
	
	'后倒俯卧上下弹动

	SPEED 10
	
	MOVE G6A,  97,  88, 112,  24, 106,  
	MOVE G6D, 105,  90, 106,  30, 108,  
	MOVE G6B,  11,  37,  88,  ,  ,  
	MOVE G6C,  12,  36,  88,  ,  ,  
	
	MOVE G6A,  94, 149,  25,  80, 106,  
	MOVE G6D,  96, 164,  21,  65, 109,  
	MOVE G6B,  17,  12, 166,  ,  ,  
	MOVE G6C,  17,  12, 166,  ,  ,  
	
	MOVE G6A,  97,  88, 112,  24, 106,  
	MOVE G6D, 105,  90, 106,  30, 108,  
	MOVE G6B,  11,  37,  88,  ,  ,  
	MOVE G6C,  12,  36,  88,  ,  ,  
	
	MOVE G6A,  94, 149,  25,  80, 106,  
	MOVE G6D,  96, 164,  21,  65, 109,  
	MOVE G6B,  17,  12, 166,  ,  ,  
	MOVE G6C,  17,  12, 166,  ,  , 
	
	MOVE G6A,  97,  88, 112,  24, 106,  
	MOVE G6D, 105,  90, 106,  30, 108,  
	MOVE G6B,  11,  37,  88,  ,  ,  
	MOVE G6C,  12,  36,  88,  ,  ,  
	
	MOVE G6A,  94, 149,  25,  80, 106,  
	MOVE G6D,  96, 164,  21,  65, 109,  
	MOVE G6B,  17,  12, 166,  ,  ,  
	MOVE G6C,  17,  12, 166,  ,  , 
	
	MOVE G6A,  97,  88, 112,  24, 106,  
	MOVE G6D, 105,  90, 106,  30, 108,  
	MOVE G6B,  11,  37,  88,  ,  ,  
	MOVE G6C,  12,  36,  88,  ,  ,  
	
	MOVE G6A,  94, 149,  25,  80, 106,  
	MOVE G6D,  96, 164,  21,  65, 109,  
	MOVE G6B,  17,  12, 166,  ,  ,  
	MOVE G6C,  17,  12, 166,  ,  , 
	
	MOVE G6A,  97,  88, 112,  24, 106,  
	MOVE G6D, 105,  90, 106,  30, 108,  
	MOVE G6B,  11,  37,  88,  ,  ,  
	MOVE G6C,  12,  36,  88,  ,  ,  
	
	DELAY 800
	
	'后倒俯卧撑

	SPEED 8
	
	MOVE G6A, 100,  14, 170, 100, 113,  
	MOVE G6D, 100,  14, 170, 101, 112,  
	MOVE G6B,  14,  23,  89,  ,  ,  
	MOVE G6C,  14,  23,  89,  ,  ,  
	
	MOVE G6A, 100,  14, 170, 100, 113,  
	MOVE G6D, 100,  14, 170, 101, 112,  
	MOVE G6B,  10,  77,  13,  ,  ,  
	MOVE G6C,  12,  73,  11,  ,  ,  
	
	MOVE G6A, 100,  14, 170, 100, 113,  
	MOVE G6D, 100,  14, 170, 101, 112,  
	MOVE G6B,  14,  23,  89,  ,  ,  
	MOVE G6C,  14,  23,  89,  ,  ,  
	
	MOVE G6A, 100,  14, 170, 100, 113,  
	MOVE G6D, 100,  14, 170, 101, 112,  
	MOVE G6B,  10,  77,  13,  ,  ,  
	MOVE G6C,  12,  73,  11,  ,  ,  
	
	MOVE G6A, 100,  14, 170, 100, 113,  
	MOVE G6D, 100,  14, 170, 101, 112,  
	MOVE G6B,  14,  23,  89,  ,  ,  
	MOVE G6C,  14,  23,  89,  ,  ,  
	
	MOVE G6A, 100,  14, 170, 100, 113,  
	MOVE G6D, 100,  14, 170, 101, 112,  
	MOVE G6B,  10,  77,  13,  ,  ,  
	MOVE G6C,  12,  73,  11,  ,  ,  
	
	MOVE G6A, 100,  14, 170, 100, 113,  
	MOVE G6D, 100,  14, 170, 101, 112,  
	MOVE G6B,  14,  23,  89,  ,  ,  
	MOVE G6C,  14,  23,  89,  ,  ,  
	
	MOVE G6A, 100,  14, 170, 100, 113,  
	MOVE G6D, 100,  14, 170, 101, 112,  
	MOVE G6B,  10,  77,  13,  ,  ,  
	MOVE G6C,  12,  73,  11,  ,  ,  
	
	
	DELAY 800		
	
	'''''后倒俯卧起来

	SPEED 8

	MOVE G6A,  94, 149,  25,  80, 106,  
	MOVE G6D,  96, 164,  21,  65, 109,  
	MOVE G6B,  11,  37,  88,  ,  ,  
	MOVE G6C,  12,  36,  88,  ,  , 

	DELAY 1000
	
	SPEED 3
	
	MOVE G6A,  95, 157,  25,  86, 105,  
	MOVE G6D,  97, 165,  21,  79, 108,  
	MOVE G6B,  40,  30,  75,  ,  ,  
	MOVE G6C,  44,  33,  89,  ,  ,  

    DELAY 300

    MOVE G6A, 100,  81, 131, 103, 106,  
	MOVE G6D, 100,  81, 131, 103, 106,  
	MOVE G6B,  97,  41,  82,  ,  ,  
	MOVE G6C,  97,  41,  82,  ,  ,  
    
    
    SPEED 8
	
	'侧躺下
	MOVE G6A,  93,  76, 145,  93, 107,  		'1  手平
	MOVE G6D,  93,  76, 145,  93, 107,  
	MOVE G6B, 145,  81,  88,  ,  ,  
	MOVE G6C, 145,  81,  88,  ,  ,  
	
	MOVE G6A,  86, 149,  25, 141, 114,  
	MOVE G6D,  93, 152,  22, 139, 106,  
	MOVE G6B, 112,  81,  88,  ,  ,  
	MOVE G6C, 105,  82,  89,  ,  ,  
	
	MOVE G6A, 121, 142,  25, 142,  98,  
	MOVE G6D,  62, 109,  89, 116, 118,  
	MOVE G6B, 104,  85,  91,  ,  ,  
	MOVE G6C, 106,  82,  90,  ,  ,  
	
	MOVE G6A, 122, 142,  25, 142,  82,  
	MOVE G6D,  54,  79, 115, 111, 112,  
	MOVE G6B, 111,  99,  98,  ,  ,  
	MOVE G6C, 106,  82,  90,  ,  ,  
	
	MOVE G6A, 103,  66, 154,  97,  81,  
	MOVE G6D, 103,  85, 115, 116, 116,  
	MOVE G6B,  99, 181, 174,  ,  ,  
	MOVE G6C, 106,  46,  90,  ,  , 
	
	DELAY 800
	
	'抠脚
	
	SPEED 10
	
	MOVE G6A, 103,  66, 154,  97,  81,  
	MOVE G6D, 103,  85, 115, 116, 116,  
	MOVE G6B,  99, 181, 174,  ,  ,  
	MOVE G6C, 103, 189, 139,  ,  ,  
	
	MOVE G6A, 103,  66, 154,  97,  81,  
	MOVE G6D, 123, 127,  24, 147, 152,  
	MOVE G6B,  99, 181, 174,  ,  ,  
	MOVE G6C, 105,  70,  79,  ,  ,  
	
	MOVE G6A, 103,  66, 154,  97,  81,  
	MOVE G6D, 103,  85, 115, 116, 116,  
	MOVE G6B,  99, 181, 174,  ,  ,  
	MOVE G6C, 103, 189, 139,  ,  ,  
	
	MOVE G6A, 103,  66, 154,  97,  81,  
	MOVE G6D, 123, 127,  24, 147, 152,  
	MOVE G6B,  99, 181, 174,  ,  ,  
	MOVE G6C, 105,  70,  79,  ,  ,  
	
	MOVE G6A, 103,  66, 154,  97,  81,  
	MOVE G6D, 103,  85, 115, 116, 116,  
	MOVE G6B,  99, 181, 174,  ,  ,  
	MOVE G6C, 103, 189, 139,  ,  ,  
	
	MOVE G6A, 103,  66, 154,  97,  81,  
	MOVE G6D, 123, 127,  24, 147, 152,  
	MOVE G6B,  99, 181, 174,  ,  ,  
	MOVE G6C, 105,  70,  79,  ,  ,  
	
	MOVE G6A, 103,  66, 154,  97,  81,  
	MOVE G6D, 103,  85, 115, 116, 116,  
	MOVE G6B,  99, 181, 174,  ,  ,  
	MOVE G6C, 103, 189, 139,  ,  ,  
	
	MOVE G6A, 103,  66, 154,  97,  81,  
	MOVE G6D, 123, 127,  24, 147, 152,  
	MOVE G6B,  99, 181, 174,  ,  ,  
	MOVE G6C, 105,  70,  79,  ,  ,  

	
	
	SPEED 6
	'侧躺起来
	MOVE G6A, 103, 124,  51, 149,  81,  
	MOVE G6D, 103, 125,  32, 161, 120,  
	MOVE G6B, 111, 177,  97,  ,  ,  
	MOVE G6C, 116,  58,  90,  ,  ,  
	
	MOVE G6A, 122, 128,  26, 161,  82,  
	MOVE G6D,  79, 123,  40, 145, 135,  
	MOVE G6B, 100,  97,  92,  ,  ,  
	MOVE G6C,  90,  58, 116,  ,  ,  
	
	MOVE G6A, 122, 128,  25, 161,  82,  
	MOVE G6D,  56,  83, 128,  99, 131,  
	MOVE G6B,  99,  66,  94,  ,  ,  
	MOVE G6C,  90,  58, 116,  ,  ,  
	
	MOVE G6A, 122, 127,  25, 161,  95,  
	MOVE G6D,  56,  83,  ,  99, 131,  
	MOVE G6B,  99,  66,  94,  ,  ,  
	MOVE G6C,  90,  58, 116,  ,  ,  
	
	MOVE G6A, 101,  91,  98, 117,  95,  
	MOVE G6D,  78,  91, 125,  91, 127,  
	MOVE G6B,  99,  66,  94,  ,  ,  
	MOVE G6C,  90,  58, 116,  ,  ,  
	
	MOVE G6A,  93,  76, 145,  93, 107,  		'1  手平
	MOVE G6D,  93,  76, 145,  93, 107,  
	MOVE G6B, 145,  81,  88,  ,  ,  
	MOVE G6C, 145,  81,  88,  ,  , 
	
	
	
	DELAY 2000
	
	MOVE G6A, 100,  81, 131, 103, 106,  
	MOVE G6D, 100,  81, 131, 103, 106,  
	MOVE G6B,  97,  41,  82,  ,  ,  
	MOVE G6C,  97,  41,  82,  ,  ,
	
	
		
	
	''''''单腿站立

	MOVE G6A, 109,  92, 119,  98,  95,  
	MOVE G6D,  93,  85, 127,  99, 103,  
	MOVE G6B, 100,  30,  80,  ,  ,  
	MOVE G6C, 100,  30,  80,  ,  ,  
	WAIT
	
	DELAY 1500
	
	SPEED 8
	
	FOR i = 1 TO 2
	
		MOVE G6A, 109,  53, 174,  98, 115,  
		MOVE G6D,  99,  80,  36, 159,  90,  
		MOVE G6B, 105,  50, 189,  ,  ,  
		MOVE G6C, 100, 150,  11,  ,  , 
		WAIT
		
		DELAY 300
		
		MOVE G6A, 109,  53, 174,  98, 115,  
		MOVE G6D,  99,  80,  36, 159,  90,  
		MOVE G6B, 106, 155,  13,  ,  ,  
		MOVE G6C,  99,  68, 188,  ,  , 
		WAIT
		
		DELAY 300
	
	NEXT i
	
	
	WAIT
 
	WAIT
	DELAY 800
	
	SPEED 5
	
	MOVE G6A, 110,  93, 108, 113,  92,  
	MOVE G6D, 90, 105,  91, 117, 105,  
	MOVE G6B, 187, 149,  51,  ,  ,  
	MOVE G6C, 185, 143,  44,  ,  ,  
	WAIT

	DELAY 300
	
	
	
	'鞠躬准备
	
	SPEED 7								
    MOVE G6A,100,  76, 145,  93, 100, 100	
    MOVE G6D,100,  76, 145,  93, 100, 100	
    MOVE G6C,140,  30,  80					
    MOVE G6B,140,  30,  80, , ,100			
    WAIT									

    SPEED 5								
    MOVE G6A,100,  76, 145,  93, 100, 100	
    MOVE G6D,100,  76, 145,  93, 100, 100	
    MOVE G6C,140,  30,  30					
    MOVE G6B,140,  30,  30, , ,130			
    WAIT			
    
    DELAY 300					

	'三次鞠躬


    MOVE G6A,100,  55, 145,  145, 100, 100	
    MOVE G6D,100,  55, 145,  145, 100, 100	
    MOVE G6C,150,  30,  25					
    MOVE G6B,150,  30,  25,					
    WAIT			

    SPEED 3									
    MOVE G6A,100,  76, 145,  93, 100, 100	
    MOVE G6D,100,  76, 145,  93, 100, 100	
    MOVE G6C,140,  30,  30					
    MOVE G6B,140,  30,  30, , ,100			
    WAIT	
     
    MOVE G6A,100,  55, 145,  145, 100, 100	
    MOVE G6D,100,  55, 145,  145, 100, 100	
    MOVE G6C,150,  30,  25					
    MOVE G6B,150,  30,  25,					
    WAIT
    
    SPEED 3									
    MOVE G6A,100,  76, 145,  93, 100, 100	
    MOVE G6D,100,  76, 145,  93, 100, 100	
    MOVE G6C,140,  30,  30					
    MOVE G6B,140,  30,  30, , ,100			
    WAIT
    
    MOVE G6A,100,  55, 145,  145, 100, 100	
    MOVE G6D,100,  55, 145,  145, 100, 100	
    MOVE G6C,150,  30,  25					
    MOVE G6B,150,  30,  25,					
    WAIT
    
    DELAY 500
    
    SPEED 3									
    MOVE G6A,100,  76, 145,  93, 100, 100	
    MOVE G6D,100,  76, 145,  93, 100, 100	
    MOVE G6C,140,  30,  30					
    MOVE G6B,140,  30,  30, , ,100			
    WAIT

 		
 		
 	'鞠躬还原并结束							

	DELAY 300

    SPEED 7								
    MOVE G6A,100,  76, 145,  93, 100, 100	
    MOVE G6D,100,  76, 145,  93, 100, 100	
    MOVE G6C,120,  30,  80					
    MOVE G6B,120,  30,  80, , ,100	
    		

	
	DELAY 10000
    

	

    ' 'GOSUB LOW_Voltage
    
    GOSUB FB_tilt_check
    GOSUB LR_tilt_check
    
    

	
 



    ERX 4800,A,MAIN				'通过RX端口接收RS232信号;4800:端口速度；A:端口号
    A_old = A
    '根据变量的值条件转移,A=0跳转到MAIN，A=1跳转到'...
    ON A GOTO MAIN,KEY1,KEY2,KEY3',KEY4,KEY5,KEY6,KEY7,KEY8,KEY9,KEY10,KEY11,KEY12,KEY13,KEY14,KEY15,KEY16,KEY17,KEY18 ,KEY19,KEY20,KEY21,KEY22,KEY23,KEY24,KEY25',KEY26,KEY27,KEY28 ,KEY29,KEY30,KEY31,KEY32
    '
    '    GOTO MAIN					跳转到MAIN	
    '*******************************************
    '*******************************************
    '*******************************************
KEY1:
    GOSUB FB_tilt_check
    GOSUB LR_tilt_check


    GOTO RX_EXIT
    '*******************************************
KEY2:
    MOVE G6A, 101,  75, 144,  94,  99,
    MOVE G6D, 101,  76, 143,  94,  99,
    MOVE G6B, 100,  30,  80,  , 74 ,
    MOVE G6C, 101,  32,  81,  ,  ,
    MOVE G6A, 101,  75, 140,  94,  99,  
	MOVE G6D, 102,  75, 141,  96,  99,  
	MOVE G6B, 102,  40, 147,  ,  ,  
	MOVE G6C, 102,  34,  82,  ,  ,  

    WAIT


    GOTO RX_EXIT
    '*******************************************
KEY3:
MOVE G6A, 101,  75, 144,  94,  99,  
MOVE G6D, 101,  76, 143,  94,  99,  
MOVE G6B, 100,  30,  80,  ,  ,  
MOVE G6C, 101,  32, 151,  ,  ,  
WAIT



    GOTO RX_EXIT


    '************************************************

RX_EXIT:

    ERX 4800, A, MAIN

    GOTO RX_EXIT
FB_tilt_check:
    '  IF tilt_check_failure = 0 THEN
    '        RETURN
    '    ENDIF
    FOR i = 0 TO COUNT_MAX
        A = AD(FB_tilt_AD_port)	'将AD端口的模拟信号赋给A
        IF A > 250 OR A < 5 THEN RETURN '返回11041行
        IF A > MIN AND A < MAX THEN RETURN '返回11041行
        DELAY tilt_time_check
    NEXT i

    IF A < MIN THEN GOSUB tilt_front '执行4654行
    IF A > MAX THEN GOSUB tilt_back '执行4660行

    GOSUB GOSUB_RX_EXIT '执行291行

    RETURN '返回11041行

LR_tilt_check:
    '  IF tilt_check_failure = 0 THEN
    '        RETURN
    '    ENDIF
    FOR i = 0 TO COUNT_MAX
        B = AD(LR_tilt_AD_port)	'
        IF B > 250 OR B < 5 THEN RETURN
        IF B > MIN AND B < MAX THEN RETURN
        DELAY tilt_time_check
    NEXT i

    IF B < MIN OR B > MAX THEN
        SPEED 8
        MOVE G6B,140,  40,  80
        MOVE G6C,140,  40,  80
        WAIT
        GOSUB standard_pose	
        RETURN

    ENDIF
    RETURN '返回11042行

GOSUB_RX_EXIT:

    ERX 4800, A, GOSUB_RX_EXIT2'蓝牙发射频率2

    GOTO GOSUB_RX_EXIT
GOSUB_RX_EXIT2:
    RETURN '返回原程序（1.4651行)
tilt_front:
    A = AD(FB_tilt_AD_port)  '将AD端口的模拟信号赋给A
    'IF A < MIN THEN GOSUB front_standup
    IF A < MIN THEN  GOSUB back_standup '执行605行
    RETURN '返回4648行
    '**************************************************
tilt_back:
    A = AD(FB_tilt_AD_port)
    'IF A > MAX THEN GOSUB back_standup
    IF A > MAX THEN GOSUB front_standup '执行661行
    RETURN '返回4650行
    '**************************************************
back_standup: '后倒自动站立

    GOSUB Arm_motor_mode1
    GOSUB Leg_motor_mode1


    SPEED 15
    MOVE G6A,100, 150, 170,  40, 100
    MOVE G6D,100, 150, 170,  40, 100
    MOVE G6B, 150, 150,  45
    MOVE G6C, 150, 150,  45
    WAIT

    SPEED 15
    MOVE G6A,  100, 155,  110, 120, 100
    MOVE G6D,  100, 155,  110, 120, 100
    MOVE G6B, 190, 80,  15
    MOVE G6C, 190, 80,  15
    WAIT

    GOSUB Leg_motor_mode2
    SPEED 15	
    MOVE G6A,  100, 165,  27, 162, 100
    MOVE G6D,  100, 165,  27, 162, 100
    MOVE G6B,  155, 15, 90
    MOVE G6C,  155, 15, 90
    WAIT


    SPEED 10	
    MOVE G6A,  100, 150,  27, 162, 100
    MOVE G6D,  100, 150,  27, 162, 100
    MOVE G6B,  140, 15, 90
    MOVE G6C,  140, 15, 90
    WAIT


    SPEED 6
    MOVE G6A,  100, 138,  27, 155, 100
    MOVE G6D,  100, 138,  27, 155, 100
    MOVE G6B, 113,  30, 80
    MOVE G6C, 113,  30, 80
    WAIT

    DELAY 100
    SPEED 10
    GOSUB stand_pose
    GOSUB Leg_motor_mode1

    RETURN
front_standup: '后倒自动站立
    GOSUB Arm_motor_mode1
    GOSUB Leg_motor_mode1


    SPEED 15
    MOVE G6A,100, 15,  70, 140, 100,
    MOVE G6D,100, 15,  70, 140, 100,
    MOVE G6B,20,  140,  15
    MOVE G6C,20,  140,  15
    WAIT

    SPEED 12
    MOVE G6A,100, 136,  35, 80, 100,
    MOVE G6D,100, 136,  35, 80, 100,
    MOVE G6B,20,  30,  80
    MOVE G6C,20,  30,  80
    WAIT

    SPEED 12
    MOVE G6A,100, 165,  70, 30, 100,
    MOVE G6D,100, 165,  70, 30, 100,
    MOVE G6B,30,  20,  95
    MOVE G6C,30,  20,  95
    WAIT

    SPEED 10
    MOVE G6A,100, 165,  45, 90, 100,
    MOVE G6D,100, 165,  45, 90, 100,
    MOVE G6B,130,  50,  60
    MOVE G6C,130,  50,  60
    WAIT

    SPEED 10
    GOSUB stand_pose

    RETURN

    '******************************************

Arm_motor_mode1:
    MOTORMODE G6B,1,1,1
    MOTORMODE G6C,1,1,1
    RETURN
Leg_motor_mode1:
    MOTORMODE G6A,1,1,1,1,1
    MOTORMODE G6D,1,1,1,1,1
    RETURN
Leg_motor_mode2:
    MOTORMODE G6A,2,2,2,2,2
    MOTORMODE G6D,2,2,2,2,2
    RETURN


start_music:
    TEMPO 220
    MUSIC "O23EAB7EA>3#C"
    RETURN
    '************************************************
stand_pose:
    MOVE G6A,100,  76, 145,  93, 100, 100
    MOVE G6D,100,  76, 145,  93, 100, 100
    MOVE G6B,100,  30,  80, 100, 100, 100
    MOVE G6C,100,  30,  80, 100, 100, 100
    WAIT
    pose = 0
    grip_pose = 0
    RETURN
standard_pose:
    MOVE G6A,100,  76, 145,  93, 100, 100
    MOVE G6D,100,  76, 145,  93, 100, 100
    MOVE G6B,100,  30,  80, 100, 100, 100
    MOVE G6C,100,  30,  80, 100, 100, 100
    WAIT
    RETURN