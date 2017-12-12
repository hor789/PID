#include<stdio.h>
#define ITERATION_NUM 500
#define SET_VALUE 300.0
#define PID_CONV_REAL 1.0
struct _pid{
	float SetSpeed;                    //设定值
	float ActualSpeed;				   //实际值
	float err;						   //偏差值
	float err_last;                    //上一次偏差值
	float err_next;                    //下一次偏差值
	float Kp, Ki, Kd;				   //设定值
	float voltage;                     //实际转换值
	float integral;					   //积分累积
	float umax;						   //偏差上限值
	float umin;						   //偏差下限值
};

void PID_Init(struct _pid *pid)
{
	printf("PID Init begin \n");
	pid->SetSpeed = 0.0;
	pid->ActualSpeed = 0.0;
	pid->err = 0.0;
	pid->err_last = 0.0;
	pid->err_next = 0.0;
	pid->voltage = 0.0;
	pid->integral = 0.0;
	pid->Kp = 0.2;
	//pid->Ki = 0.015;
	//pid->Ki = 0.04;
	//pid->Ki = 0.1;
	pid->Ki = 0.2;
	pid->Kd = 0.2;
	pid->umax = 400;
	pid->umin = -200;
	printf("PID Init end \n");
}
 //标准PID公式
float PID_SpeedOut(struct _pid *pid,float speed)
{
	pid->SetSpeed = speed;
	pid->err = pid->SetSpeed - pid->ActualSpeed;
	pid->integral += pid->err;
	pid->voltage = pid->Kp*pid->err + pid->Ki*pid->integral + pid->Kd*(pid->err - pid->err_last);
	pid->err_last = pid->err;
	pid->ActualSpeed = pid->voltage * PID_CONV_REAL;
	return pid->ActualSpeed;
}
//利用PID增量的PID公式
float PID_Speed_Incr(struct _pid *pid, float speed)
{
	pid->SetSpeed = speed;
	pid->err = pid->SetSpeed - pid->ActualSpeed;
	float increment = pid->Kp*(pid->err - pid->err_next) + pid->Ki*pid->err + pid->Kd*(pid->err - 2*pid->err_next + pid->err_last);
	pid->ActualSpeed += increment;
	pid->err_last = pid->err_next;
	pid->err_next = pid->err;
	return pid->ActualSpeed;
}

float PID_Integral1(struct _pid *pid, float speed)
{
	float index;
	pid->SetSpeed = speed;
	pid->err = pid->SetSpeed - pid->ActualSpeed;
	if (abs(pid->err) > 200)
	{
		index = 0;
	}
	else
	{
		index = 1.0;
		pid->integral += pid->err;
	}
	pid->voltage = pid->Kp*pid->err + index * pid->Ki*pid->integral + pid->Kd*(pid->err - pid->err_last);
	pid->err_last = pid->err;
	pid->ActualSpeed = pid->voltage * PID_CONV_REAL;
	return pid->ActualSpeed;
}
//积分分离
float PID_Integral2(struct _pid *pid, float speed)
{
	float index;
	pid->SetSpeed = speed;
	pid->err = pid->SetSpeed - pid->ActualSpeed;
	if (pid->ActualSpeed > pid->umax)
	{
		if (abs(pid->err) > 200)
		{
			index = 0;
		}
		else
		{
			index = 1.0;
			if (pid->err < 0)
				pid->integral += pid->err;
		}
	}
	else if (pid->ActualSpeed < pid->umin)
	{
		if (abs(pid->err) > 200)
		{
			index = 0;
		}
		else
		{
			index = 1.0;
			if (pid->err > 0)
				pid->integral += pid->err;
		}
	}
	else
	{
		if (abs(pid->err) > 200)
		{
			index = 0;
		}
		else
		{
			index = 1.0;
			pid->integral += pid->err;
		}
	}

	pid->voltage = pid->Kp*pid->err + index * pid->Ki*pid->integral + pid->Kd*(pid->err - pid->err_last);
	pid->err_last = pid->err;
	pid->ActualSpeed = pid->voltage * PID_CONV_REAL;
	return pid->ActualSpeed;
}
//变积分PID公式 ： Ki*index
float PID_Integral3(struct _pid *pid, float speed)
{
	float index;
	pid->SetSpeed = speed;
	pid->err = pid->SetSpeed - pid->ActualSpeed;
		if (abs(pid->err) > 200)
		{
			index = 0;
		}
		else
		{
			if (abs(pid->err) < 180)
				index = 1.0;
			else
				index = (200 - abs(pid->err)) / 20;
			pid->integral += pid->err;
		}
	pid->voltage = pid->Kp*pid->err + index * pid->Ki*pid->integral + pid->Kd*(pid->err - pid->err_last);
	pid->err_last = pid->err;
	pid->ActualSpeed = pid->voltage * PID_CONV_REAL;
	return pid->ActualSpeed;
}
//抗积分饱和（设置上下限），积分分离，变积分Ki*index
float PID_Integral4(struct _pid *pid, float speed)
{
	float index;
	pid->SetSpeed = speed;
	pid->err = pid->SetSpeed - pid->ActualSpeed;
	if (pid->ActualSpeed > pid->umax)
	{
		if (abs(pid->err) > 200)
		{
			index = 0;
		}
		else
		{
			if (abs(pid->err) < 180)
				index = 1.0;
			else
				index = (200 - abs(pid->err)) / 20;
			if (pid->err < 0)
				pid->integral += pid->err;
		}
	}
	else if (pid->ActualSpeed < pid->umin)
	{
		if (abs(pid->err) > 200)
		{
			index = 0;
		}
		else
		{
			if (abs(pid->err) < 180)
				index = 1.0;
			else
				index = (200 - abs(pid->err)) / 20;
			if (pid->err > 0)
				pid->integral += pid->err;
		}
	}
	else
	{
		if (abs(pid->err) > 200)
		{
			index = 0;
		}
		else
		{
			if (abs(pid->err) < 180)
				index = 1.0;
			else
				index = (200 - abs(pid->err)) / 20;
			pid->integral += pid->err;
		}
	}

	pid->voltage = pid->Kp*pid->err + index * pid->Ki*pid->integral + pid->Kd*(pid->err - pid->err_last);
	pid->err_last = pid->err;
	pid->ActualSpeed = pid->voltage * PID_CONV_REAL;
	return pid->ActualSpeed;
}
void main()
{
	printf("System begin \n");
	struct _pid *pid = (struct _pid *)malloc(sizeof(pid));
	PID_Init(&pid);
	int count = 0;
	while (count < ITERATION_NUM)
	{
		//float speed = PID_SpeedOut(&pid,SET_VALUE);
		//float speed = PID_Speed_Incr(&pid, SET_VALUE);
		//float speed = PID_Integral1(&pid, SET_VALUE);
		//float speed = PID_Integral2(&pid, SET_VALUE);
		//float speed = PID_Integral3(&pid, SET_VALUE);
		float speed = PID_Integral4(&pid, SET_VALUE);
		printf("%f\n",speed);
		count++;
	}
	system("pause");
	//free(pid);
}