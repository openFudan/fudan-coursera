DIM A AS BYTE
DIM I AS BYTE

PTP SETON 				
PTP ALLON

DIR G6A,1,0,0,1,0,0		'motor0~5
DIR G6B,1,1,1,1,1,1		'motor6~11
DIR G6C,0,0,0,0,0,0		'motor12~17
DIR G6D,0,1,1,0,1,0		'motor18~23

GETMOTORSET G6A,1,1,1,1,1,0
GETMOTORSET G6B,1,1,1,0,0,0
GETMOTORSET G6C,1,1,1,0,0,0
GETMOTORSET G6D,1,1,1,1,1,0

SPEED 5

MOTOR G24

MAIN:
	GOSUB cheer_up
	DELAY 1000
	'GOSUB stand_pose
	'DELAY 1000
	
	
	
cheer_up:
	SPEED 10
	MOVE G6A, 100,  76, 145,  93, 100,  
	MOVE G6D, 100,  76, 145,  93, 100,  
	MOVE G6B, 100,  ,  ,  ,  ,  
	MOVE G6C, 100,  ,  ,  ,  ,  

	WAIT
	RETURN
	
stand_pose:
	SPEED 10
	MOVE G6A, 100,  76, 145,  93, 100,  
	MOVE G6D, 100,  76, 145,  93, 100,  
	MOVE G6B, 100,  30,  80,  ,  ,  
	MOVE G6C, 100,  30,  80,  ,  ,  

	WAIT
	RETURN