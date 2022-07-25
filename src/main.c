#include "lcd/lcd.h"
#include <string.h>
#include "utils.h"
#include "img.h"
#include <stdio.h>
#include <time.h>
int score=0;
void Inp_init(void)
{
    gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_8);
}

void Adc_init(void) 
{
    rcu_periph_clock_enable(RCU_GPIOA);
    gpio_init(GPIOA, GPIO_MODE_AIN, GPIO_OSPEED_50MHZ, GPIO_PIN_0|GPIO_PIN_1);
    RCU_CFG0|=(0b10<<14)|(1<<28);
    rcu_periph_clock_enable(RCU_ADC0);
    ADC_CTL1(ADC0)|=ADC_CTL1_ADCON;
}

void IO_init(void)
{
    Inp_init(); // inport init
    Adc_init(); // A/D init
    Lcd_Init(); // LCD init
}
void cactus(){
}
bool lose_judge(int trex_x,int trex_y,int cactus_x,int cactus_y,int cactus_group,int result){
	if(cactus_group==0){//one cactus
		if(((cactus_x-trex_x<=15)&&(cactus_x-trex_x>=0))||((trex_x-cactus_x<=9)&&(trex_x-cactus_x>=0))){
			if(cactus_y-trex_y<=16){
				return 1;
			}
		}		
	}
	else if(cactus_group==1){//two cactus
        if(((cactus_x-trex_x<=15)&&(cactus_x-trex_x>=0))||((trex_x-cactus_x<=20)&&(trex_x-cactus_x>=0))){
			if(cactus_y-trex_y<=20){
				return 1;
		}
	}
	}
	else if(cactus_group==2){
        if(((cactus_x-trex_x<=15)&&(cactus_x-trex_x>=0))||((trex_x-cactus_x<=32)&&(trex_x-cactus_x>=0))){
			if(cactus_y-trex_y<=20){
				return 1;
		}
	}		
	}
	else{
		if(((cactus_x-trex_x<=15)&&(cactus_x-trex_x>=0))||((trex_x-cactus_x<=15)&&(trex_x-cactus_x>=0))){
			if(!Get_Button(0)){
				return 1;
			}
		}
	}
	return 0;
}
void generate_cactus1(int cactus_x,int cactus_y){
		LCD_ShowPic(cactus_x,cactus_y,cactus_x+11,cactus_y+19,cactus1);
}
void generate_cactus2(int cactus_x,int cactus_y){
		LCD_ShowPic(cactus_x,cactus_y,cactus_x+11,cactus_y+19,cactus2);
}
void generate_pter(int cactus_x,int cactus_y,int *pter_status){
	if(*pter_status==0){
		LCD_ShowPic(cactus_x,cactus_y-5-10,cactus_x+19,cactus_y-15+19,pter1);
		*pter_status=1;
	}
	else{
		LCD_ShowPic(cactus_x,cactus_y-5-10,cactus_x+19,cactus_y-15+19,pter2);
		*pter_status=0;
	}
}
void fill_for_generate_cactus(int cactus_x,int cactus_y,int cactus_group){
	if(cactus_group==0){
		fill(cactus_x,cactus_y,cactus_x+11,cactus_y+19,BLACK);
	}
	else if(cactus_group==1){
		LCD_Fill(cactus_x,cactus_y,cactus_x+23,cactus_y+19,BLACK);
	}
	else if(cactus_group==2){
		LCD_Fill(cactus_x,cactus_y,cactus_x+35,cactus_y+19,BLACK);
	}
	else{
		LCD_Fill(cactus_x,cactus_y-10-5,cactus_x+20,cactus_y+9-5,BLACK);
	}
}
int trexx1=5;
int trexy1=50;
int trexx2=24;
int trexy2=69;
int main(void)
{
    IO_init();  
    wait_for_start();
	int flag=0;
	int index = 0;//index of difficulty,the inital difficulty is easy 0
		play_setting();
		while(1){
			if(Get_Button(1)){
				setting();
				delay_1ms(1500);
				while(1){		
					if(Get_Button(1)){
						index = 1;
						flag=1;
						break;
					}//the difficulty is hard	
					if(Get_Button(0)){
						index =0;
						flag=1;
						break;
					}
				}
				
			}//enter setting	
			//break;
			if(flag) break;	
		}
	LCD_Clear(BLACK);
	unsigned char g[3200];
	int whichg=0;
	int g1len=160;
	int gspeed=8;
    int g1head=0;

    int up=1;
    int upboard=6;
    bool overboard=0;
	int lose=0;
    /*cactus parameter*/
    int cactus_x=148;
	int cactus_x2=148;
	int cactus_x3=148;
    int cactus_y=50;
    int cactus_group=0;//the different group of cactus
	int random_num=0;
	int step_back=4;
	if(index==1)step_back=5;//hard difficulty
	/*pter paramater*/
	int pter_status=0; 
    while(1){ 
		if(lose) break;
    	if(Get_Button(0)){//no jump
    		//LCD_Fill(5,50,31,79,BLACK);
    		LCD_Fill(5,50,31,79,BLACK);
	    	LCD_ShowPic(5,50,31,69,trex4); 
	    	//LCD_ShowPic(g1head,70,g1head+159,79,g1);
			if(whichg==0){
				for(int j=1;j<=20;j++){
					memcpy(g+160*(j-1),g1+160*(j-1)+(160-g1len),g1len);
					memcpy(g+160*(j-1)+g1len,g2+160*(j-1),(160-g1len));
				}

				LCD_ShowPic(0,70,159,79,g);
				g1len-=gspeed;
				if(g1len<=0){
					g1len=0;
					whichg=1;
				} 
			}
			else if(whichg==1){
				for(int j=1;j<=20;j++){
					memcpy(g+160*(j-1),g2+160*(j-1)+g1len,(160-g1len));
					memcpy(g+160*(j-1)+(160-g1len),g1+160*(j-1),g1len);
				}
				LCD_ShowPic(0,70,159,79,g);
				g1len+=gspeed;
				if(g1len>=160){
					g1len=160;
					whichg=0;
				} 
			}
			
			fill_for_generate_cactus(cactus_x,cactus_y,cactus_group);
	    	cactus_x-=step_back;
			cactus_x2-=step_back;
			cactus_x3-=step_back;
		    if(cactus_x<=0){
				if(cactus_group==0||cactus_group==3){
				random_num=rand()%2;
				cactus_group=rand()%4;
				if(cactus_group==0)cactus_x=148;//one cactus
				else if(cactus_group==1){
					cactus_x=136;//two cactus
					cactus_x2=148;
				} 
				else if(cactus_group==2) {
					cactus_x=124;//three cactus
					cactus_x2=136;
					cactus_x3=148;
				}
				else cactus_x=140;					
				}
				else if(cactus_group==1){
					cactus_x=cactus_x;
					cactus_group--;
				}
				else if(cactus_group==2){
					cactus_x=cactus_x2;
					cactus_x2=cactus_x3;
					cactus_group--;
					random_num=1;
				}
		    } 
	    	if(cactus_group==0) {
				if(random_num==0){
					generate_cactus1(cactus_x,cactus_y);
				}
				else{
					generate_cactus2(cactus_x,cactus_y);
				}
			}
			else if(cactus_group==1){
				if(random_num==0){
					generate_cactus1(cactus_x,cactus_y);
					generate_cactus1(cactus_x2,cactus_y);
				}
				else{
					generate_cactus2(cactus_x,cactus_y);
					generate_cactus2(cactus_x2,cactus_y);
				}				
			}
			else if(cactus_group==2){
				generate_cactus2(cactus_x,cactus_y);
				generate_cactus2(cactus_x2,cactus_y);
				generate_cactus2(cactus_x3,cactus_y);				
			}
			else{
				generate_pter(cactus_x,cactus_y,&pter_status);
			}
			if(lose_judge(trexx1,trexy1,cactus_x,cactus_y,cactus_group,score)){
				lose=1;
				break;
			} 
	    	delay_1ms(60); 
	    	LCD_ShowPic(5,50,31,69,trex5); 
	    	//LCD_ShowPic(g1head,70,g1head+159,79,g2);

			
			fill_for_generate_cactus(cactus_x,cactus_y,cactus_group);
	    	cactus_x-=step_back;
			cactus_x2-=step_back;
			cactus_x3-=step_back;
		    if(cactus_x<=0){
				if(cactus_group==0||cactus_group==3){
				random_num=rand()%2;
				cactus_group=rand()%4;
				if(cactus_group==0)cactus_x=148;//one cactus
				else if(cactus_group==1){
					cactus_x=136;//two cactus
					cactus_x2=148;
				} 
				else if(cactus_group==2) {
					cactus_x=124;//three cactus
					cactus_x2=136;
					cactus_x3=148;
				}
				else cactus_x=140;					
				}
				else if(cactus_group==1){
					cactus_x=cactus_x;
					cactus_group--;
				}
				else if(cactus_group==2){
					cactus_x=cactus_x2;
					cactus_x2=cactus_x3;
					cactus_group--;
					random_num=1;
				}
		    } 
			if(cactus_group==0) {
				if(random_num==0){
					generate_cactus1(cactus_x,cactus_y);
				}
				else{
					generate_cactus2(cactus_x,cactus_y);
				}
			}
			else if(cactus_group==1){
				if(random_num==0){
					generate_cactus1(cactus_x,cactus_y);
					generate_cactus1(cactus_x2,cactus_y);
				}
				else{
					generate_cactus2(cactus_x,cactus_y);
					generate_cactus2(cactus_x2,cactus_y);
				}				
			}
			else if(cactus_group==2){
				generate_cactus2(cactus_x,cactus_y);
				generate_cactus2(cactus_x2,cactus_y);
				generate_cactus2(cactus_x3,cactus_y);				
			}
			else{
				generate_pter(cactus_x,cactus_y,&pter_status);
			}
			delay_1ms(60); 
			if(score<10){
				update(score,1,lose);
			}
			else if(score<100){
				update(score,2,lose);
			}
			else if(score<1000){
				update(score,3,lose);
			}		
			else{
					update(score,4,lose);
				}
    	    }
    	else if(Get_Button(1)){
    		overboard=0;
    		up=1; 
    		LCD_Fill(5,50,31,79,BLACK);
			LCD_ShowPic(trexx1,trexy1,trexx2,trexy2,trex3); 
    		//LCD_Fill(5,50,31,79,BLACK);
    		while(1){
			fill_for_generate_cactus(cactus_x,cactus_y,cactus_group);
    		 	
	    	cactus_x-=step_back;
			cactus_x2-=step_back;
			cactus_x3-=step_back;
		    if(cactus_x<=0){
				if(cactus_group==0||cactus_group==3){
				random_num=rand()%2;
				cactus_group=rand()%4;
				if(cactus_group==0)cactus_x=148;//one cactus
				else if(cactus_group==1){
					cactus_x=136;//two cactus
					cactus_x2=148;
				} 
				else if(cactus_group==2) {
					cactus_x=124;//three cactus
					cactus_x2=136;
					cactus_x3=148;
				}
				else cactus_x=140;					
				}
				else if(cactus_group==1){
					cactus_x=cactus_x2;
					cactus_group--;
				}
				else if(cactus_group==2){
					cactus_x=cactus_x2;
					cactus_x2=cactus_x3;
					cactus_group--;
				}
		    } 
	    	if(cactus_group==0) {
				if(random_num==0){
					generate_cactus1(cactus_x,cactus_y);
				}
				else{
					generate_cactus2(cactus_x,cactus_y);
				}
			}
			else if(cactus_group==1){
				if(random_num==0){
					generate_cactus1(cactus_x,cactus_y);
					generate_cactus1(cactus_x2,cactus_y);
				}
				else{
					generate_cactus2(cactus_x,cactus_y);
					generate_cactus2(cactus_x2,cactus_y);
				}				
			}
			else if(cactus_group==2){
				generate_cactus2(cactus_x,cactus_y);
				generate_cactus2(cactus_x2,cactus_y);
				generate_cactus2(cactus_x3,cactus_y);				
			}
			else{
				generate_pter(cactus_x,cactus_y,&pter_status);
			}
				if(lose_judge(trexx1,trexy1,cactus_x,cactus_y,cactus_group,score)){
					lose=1;
					break;
				} 
			if(whichg==0){
				for(int j=1;j<=20;j++){
					memcpy(g+160*(j-1),g1+160*(j-1)+(160-g1len),g1len);
					memcpy(g+160*(j-1)+g1len,g2+160*(j-1),(160-g1len));
				}

				LCD_ShowPic(0,70,159,79,g);
				g1len-=gspeed;
				if(g1len<=0){
					g1len=0;
					whichg=1;
				} 
			}
			else if(whichg==1){
				for(int j=1;j<=20;j++){
					memcpy(g+160*(j-1),g2+160*(j-1)+g1len,(160-g1len));
					memcpy(g+160*(j-1)+(160-g1len),g1+160*(j-1),g1len);
				}
				LCD_ShowPic(0,70,159,79,g);
				g1len+=gspeed;
				if(g1len>=160){
					g1len=160;
					whichg=0;
				} 
			}
    			delay_1ms(60); 
				fill_for_generate_cactus(cactus_x,cactus_y,cactus_group);
    		 //	LCD_ShowPic(g1head,70,g1head+159,79,g2);
    		 	
	    	cactus_x-=step_back;
			cactus_x2-=step_back;
			cactus_x3-=step_back;
		    if(cactus_x<=0){
				if(cactus_group==0||cactus_group==3){
				random_num=rand()%2;
				cactus_group=rand()%4;
				if(cactus_group==0)cactus_x=148;//one cactus
				else if(cactus_group==1){
					cactus_x=136;//two cactus
					cactus_x2=148;
				} 
				else if(cactus_group==2) {
					cactus_x=124;//three cactus
					cactus_x2=136;
					cactus_x3=148;
				}
				else cactus_x=140;					
				}
				else if(cactus_group==1){
					cactus_x=cactus_x2;
					cactus_group--;
				}
				else if(cactus_group==2){
					cactus_x=cactus_x2;
					cactus_x2=cactus_x3;
					cactus_group--;
				}
		    } 
	    		LCD_Fill(trexx1,trexy1,trexx2,trexy2,BLACK);
				 
	    		if(!overboard){
		    		trexy1-=7;
		    		trexy2-=7;
	    		}
	    		else{
		               trexy1+=7;
		    		trexy2+=7;
                    }
	    		LCD_ShowPic(trexx1,trexy1,trexx2,trexy2,trex3); 
	    		if(!overboard) up++;
	    		else up--;
	    		if(up==upboard) overboard=1;	
	    		if(up==1) break;
				score++;
				if(cactus_group==0) {
				if(random_num==0){
					generate_cactus1(cactus_x,cactus_y);
				}
				else{
					generate_cactus2(cactus_x,cactus_y);
				}
			}
			else if(cactus_group==1){
				if(random_num==0){
					generate_cactus1(cactus_x,cactus_y);
					generate_cactus1(cactus_x2,cactus_y);
				}
				else{
					generate_cactus2(cactus_x,cactus_y);
					generate_cactus2(cactus_x2,cactus_y);
				}				
			}
			else if(cactus_group==2){
				generate_cactus2(cactus_x,cactus_y);
				generate_cactus2(cactus_x2,cactus_y);
				generate_cactus2(cactus_x3,cactus_y);				
			}
			else{
				generate_pter(cactus_x,cactus_y,&pter_status);
			}
				delay_1ms(60);
				if(score<10){
				update(score,1,lose);
				}
				else if(score<100){
				update(score,2,lose);
				}
				else if(score<1000){
				update(score,3,lose);
				}		
				else{
				update(score,4,lose);
				}	
    		}
    	} 
    	else{
		    LCD_Fill(5,50,31,79,BLACK);
	    	LCD_ShowPic(5,50,24,69,trex1); 
			if(whichg==0){
				for(int j=1;j<=20;j++){
					memcpy(g+160*(j-1),g1+160*(j-1)+(160-g1len),g1len);
					memcpy(g+160*(j-1)+g1len,g2+160*(j-1),(160-g1len));
				}

				LCD_ShowPic(0,70,159,79,g);
				g1len-=gspeed;
				if(g1len<=0){
					g1len=0;
					whichg=1;
				} 
			}
			else if(whichg==1){
				for(int j=1;j<=20;j++){
					memcpy(g+160*(j-1),g2+160*(j-1)+g1len,(160-g1len));
					memcpy(g+160*(j-1)+(160-g1len),g1+160*(j-1),g1len);
				}
				LCD_ShowPic(0,70,159,79,g);
				g1len+=gspeed;
				if(g1len>=160){
					g1len=160;
					whichg=0;
				} 
			}
			fill_for_generate_cactus(cactus_x,cactus_y,cactus_group);
			cactus_x-=step_back;
			cactus_x2-=step_back;
			cactus_x3-=step_back;
		    if(cactus_x<=0){
				if(cactus_group==0||cactus_group==3){
				random_num=rand()%2;
				cactus_group=rand()%4;
				if(cactus_group==0)cactus_x=148;//one cactus
				else if(cactus_group==1){
					cactus_x=136;//two cactus
					cactus_x2=148;
				} 
				else if(cactus_group==2) {
					cactus_x=124;//three cactus
					cactus_x2=136;
					cactus_x3=148;
				}
				else cactus_x=140;					
				}
				else if(cactus_group==1){
					cactus_x=cactus_x2;
					cactus_group--;
				}
				else if(cactus_group==2){
					cactus_x=cactus_x2;
					cactus_x2=cactus_x3;
					cactus_group--;
				}
		    }
	    	if(cactus_group==0) {
				if(random_num==0){
					generate_cactus1(cactus_x,cactus_y);
				}
				else{
					generate_cactus2(cactus_x,cactus_y);
				}
			}
			else if(cactus_group==1){
				if(random_num==0){
					generate_cactus1(cactus_x,cactus_y);
					generate_cactus1(cactus_x2,cactus_y);
				}
				else{
					generate_cactus2(cactus_x,cactus_y);
					generate_cactus2(cactus_x2,cactus_y);
				}				
			}
			else if(cactus_group==2){
				generate_cactus2(cactus_x,cactus_y);
				generate_cactus2(cactus_x2,cactus_y);
				generate_cactus2(cactus_x3,cactus_y);				
			}
			else{
				generate_pter(cactus_x,cactus_y,&pter_status);
			}
			if(lose_judge(trexx1,trexy1,cactus_x,cactus_y,cactus_group,score)){
				lose=1;
				break;
			} 
	    	delay_1ms(60); 
	    	LCD_ShowPic(5,50,24,69,trex2); 
	    	//LCD_ShowPic(g1head,70,g1head+159,79,g2);
			fill_for_generate_cactus(cactus_x,cactus_y,cactus_group);					
	    	cactus_x-=step_back;
			cactus_x2-=step_back;
			cactus_x3-=step_back;
		    if(cactus_x<=0){
				if(cactus_group==0||cactus_group==3){
				random_num=rand()%2;
				cactus_group=rand()%4;
				if(cactus_group==0)cactus_x=148;//one cactus
				else if(cactus_group==1){
					cactus_x=136;//two cactus
					cactus_x2=148;
				} 
				else if(cactus_group==2) {
					cactus_x=124;//three cactus
					cactus_x2=136;
					cactus_x3=148;
				}
				else cactus_x=140;					
				}
				else if(cactus_group==1){
					cactus_x=cactus_x2;
					cactus_group--;
				}
				else if(cactus_group==2){
					cactus_x=cactus_x2;
					cactus_x2=cactus_x3;
					cactus_group--;
				}
		    }
			if(cactus_group==0) {
				if(random_num==0){
					generate_cactus1(cactus_x,cactus_y);
				}
				else{
					generate_cactus2(cactus_x,cactus_y);
				}
			}
			else if(cactus_group==1){
				if(random_num==0){
					generate_cactus1(cactus_x,cactus_y);
					generate_cactus1(cactus_x2,cactus_y);
				}
				else{
					generate_cactus2(cactus_x,cactus_y);
					generate_cactus2(cactus_x2,cactus_y);
				}				
			}
			else if(cactus_group==2){
				generate_cactus2(cactus_x,cactus_y);
				generate_cactus2(cactus_x2,cactus_y);
				generate_cactus2(cactus_x3,cactus_y);				
			}
			else{
				generate_pter(cactus_x,cactus_y,&pter_status);
			}	
			delay_1ms(60);
			if(score<10){
				update(score,1,lose);
			}
			else if(score<100){
				update(score,2,lose);
			}
			else if(score<1000){
				update(score,3,lose);
			}		
			else{
					update(score,4,lose);
				}  	
	}
	score++;
}
LCD_ShowPic(trexx1,trexy1,trexx2,trexy2,trex1);
//gameover();
if(score<10){
	update(score,1,lose);
}
else if(score<100){
	update(score,2,lose);
}
else if(score<1000){
	update(score,3,lose);
}		
else{
		update(score,4,lose);
	}
	return 0;
}
