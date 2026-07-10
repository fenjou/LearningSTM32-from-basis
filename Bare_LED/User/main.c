#define RCC_APB2ENR     (*((volatile unsigned int*)0x40021018))//时钟使能寄存器
#define GPIOA_CRL       (*((volatile unsigned int*)0x40010800))//GPIOA低配置寄存器
#define GPIOA_ODR        (*((volatile unsigned int*)0x4001080C))//GPIOA数据输出寄存器
	
void delay(volatile unsigned int count){
	while(count--){
	
	}
}

int main(void){

	RCC_APB2ENR |= (1 << 2 );// 查手册可知，RCC_APB2ENR 的第 2 位 (IOPAEN) 控制 GPIOA 的时钟
	GPIOA_CRL &= ~(0xF << 20);// CNF5 (位23:22) 设为 00 (通用推挽)，MODE5 (位21:20) 设为 11 (50MHz输出)。
	GPIOA_CRL |= (0x3 << 20);// 推挽＋50MHz的二进制编码为0011，十六进制为0x3
	//缺陷：未加While(1)进行死循环
	while(1){
	GPIOA_ODR |= (1 << 5);//要是Pin5变为3.3V,让0001 0000和0x0按位或
	delay(1000000);//缺陷：10000太小，加到1000000
	
	GPIOA_ODR &= ~(1 << 5);
	delay(1000000);//最后没电亮，是因为复位按钮卡住了（已解决）
	}
}