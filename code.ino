#include<LedControl.h>
const int din=13 ;
const int load=12 ;
const int clk=11 ;
const int nb_led_matrix=1 ;
const int  pin_bh=3 ;
const int pin_bb=2 ;
const int pin_bd=1 ;
const int pin_bg=0 ;

bool etat_but_droite ;
bool etat_but_gauche ;
bool etat_but_haut ;
bool etat_but_bas ;

int dir ;//0 droite , 1 gauche ,2 haut , 3bas 

int snake_ligne[64] ;
int snake_col[64] ;

int apple_ligne ;
int apple_col ;

int snake_len=1 ;

LedControl lc(din,clk,load,nb_led_matrix)  ;
void setup() { 
  lc.shutdown(0,false) ;
  lc.setIntensity(0,12) ;
  lc.clearDisplay(0) ;
  pinMode(pin_bh,INPUT_PULLUP) ;
  pinMode(pin_bb,INPUT_PULLUP) ;
  pinMode(pin_bd,INPUT_PULLUP) ;
  pinMode(pin_bg,INPUT_PULLUP) ;
  randomSeed(analogRead(0)) ;
  dir=random(4) ;
  snake_ligne[0]=random(8) ;
  snake_col[0]=random(8) ;
  new_apple() ;
}
void loop() {
  click_bouton();
  update_snake() ;
  display_snake() ;
  delay(200) ;
}
void display_snake() { 
  lc.clearDisplay(0) ;
  for (int j=0;j<snake_len;j++) {
  lc.setLed(0,snake_ligne[j],snake_col[j],HIGH) ;
  }
  lc.setLed(0,apple_ligne,apple_col,HIGH) ;
}
void click_bouton() { 
  etat_but_droite=digitalRead(pin_bd) ;
  etat_but_gauche=digitalRead(pin_bg) ;
  etat_but_haut=digitalRead(pin_bh) ;
  etat_but_bas=digitalRead(pin_bb) ;

  if (etat_but_droite==true and dir!=1) { 
    dir=0 ;
    
  }
  else if (etat_but_gauche==true and dir!=0 ) { 
    dir=1 ;
  }
  else if (etat_but_haut==true and dir!=3 ) { 
    dir=2 ;
  }
  else if (etat_but_bas==true and dir!=2 ) { 
    dir=3 ;
  }
}
void update_snake() { 
  int new_head_ligne=snake_ligne[0] ;
  int new_head_col=snake_col[0] ;
  if (dir==0) { 
    new_head_col++ ;
    if (new_head_col==8) { 
      new_head_col=0 ;
    }
  }
  else if (dir==1) { 
    new_head_col-- ;
    if (new_head_col==-1) { 
      new_head_col=7 ;
    }
  }
  else if (dir==2) { 
    new_head_ligne-- ;
    if (new_head_ligne==-1) { 
      new_head_ligne=7 ;
    }
  }
  else if (dir==3) { 
    new_head_ligne++ ;
    if(new_head_ligne==8) { 
      new_head_ligne=0 ;
    }
  }
  
  if (new_head_ligne==apple_ligne and new_head_col==apple_col ) { 
    snake_len=snake_len+1 ;
    new_apple() ;
  }
  else if (sanke_collision(new_head_ligne,new_head_col)==true) {
    snake_len=1 ;
    snake_ligne[0]=random(8) ;
    snake_col[0]=random(8) ;
    dir=random(4) ;
    new_apple() ;
  }
  else {
    for (int i=snake_len-1;i>0;i--) {
      snake_ligne[i]=snake_ligne[i-1] ;
      snake_col[i]=snake_col[i-1] ;
    }
    snake_ligne[0]=new_head_ligne ;
    snake_col[0]=new_head_col ;
  }
}

bool sanke_collision(int ligne,int col) { 
  for (int i=1;i<snake_len;i++) { 
    if (ligne==snake_ligne[i] and col==snake_col[i]){
      return(true) ;
    }
  }
  return(false) ;
}
void new_apple() {
  apple_ligne=random(8) ;
  apple_col=random(8) ;
}
