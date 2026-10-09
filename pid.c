#include <stdio.h>

static const float Kp = 3.0f;   //比例系数
static const float Ki = 0.30f;  //积分系数
static const float Kd = 8.0f;   //微分系数 
const float dt = 0.2f;  //采样周期
const float target = 100.0f;  //目标温度
const float ambient = 25.0f;  //环境温度
const float tau =10.0f;  //被控对象惯性
float temp,integral,prev,t,error,deriv,power;  //当前温度，积分累计值，上一拍测量值，时间，误差，微分，功率

int main()
{
    temp = ambient;
    integral = 0.0f;
    prev = temp;

    printf("  t(s)   温度   加热功率 %%\n");
    for(int i=0;i<300;i++)
    {
        t = i * dt;  
        error = target - temp;
        integral += Ki * error * dt;  //积累误差
        deriv = -(temp - prev) / dt;  //微分涨幅
        prev = temp;
        power = Kp * error + integral + Kd * deriv;  

        if (power > 100.0f) power = 100.0f;
        if (power < 0.0f) power = 0.0f;

        temp += (ambient - temp + power) * dt / tau;

        if(i % 30 == 0) printf("%5.1f  %6.2f  %8.1f\n", (double)t, (double)temp, (double)power);
    }
    return 0;
}