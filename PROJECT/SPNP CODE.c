#include <stdio.h>
#include "user.h"
 
#define MAX_ITERATIONS 10
#define MAX_ERROR 1e-7 

/* global variables */ 
double pin = 0.9;
double pout;
double u;
double pv = 0.1;
double pnv;
double prt = 0.4;
double pnrt;
double pmove = 0.101;
double l = 0.4;
double penter;
double v;
double lh = 0.01;
double lv1 = 0.01;
double lv2 = 0.01;
double a;
double pa;
double pstay;
double timeVal; 
 
/* Prototype for the function(s) */ 

double r4 ();
double BN ();
double BH ();
double thu ();
double BNH ();
double LC ();
double LW ();


/* ================= OPTIONS ================ */
void options() { 

  pout = 1-pin;
  u = 1.0/1.76;
  pnv = 1-pv;
  pnrt = 1-prt;
  penter = (pin*pmove)/pout;
  v = 1.0/1.5;
  a = v/(u+v);
  pa = (pmove-pv)/pnv;
  pstay = 1-pa;
}

/* ========= DEFINITION OF THE NET ========== */
void net() { 

  /* === PARAM VARIABLES === */
  parm("lh");
  parm("lv1");
  parm("lv2");
  /*  ======  PLACE  ======  */ 
  place("P1");
  place("P4");
  place("P5");
  place("P8");
  place("P9");
  place("P10");
  place("P11");
  place("P12");
  place("P13");
  place("resource_cdma");
  init("resource_cdma",3);
  place("resource_ieee");
  init("resource_ieee",9);
  place("user_cdma");
  place("user_ieee");

  /*  ======  TRANSITION  ======  */ 
  /* Immediate Transitions */ 
  imm("vehicular");
  priority("vehicular",1);
  probval("vehicular",pv);
  imm("nonvehicular");
  priority("nonvehicular",1);
  probval("nonvehicular",pnv);
  imm("RT");
  priority("RT",1);
  probval("RT",prt);
  imm("NRT");
  priority("NRT",1);
  probval("NRT",pnrt);
  imm("moveout");
  priority("moveout",1);
  probval("moveout",pa);
  imm("stay");
  priority("stay",1);
  probval("stay",pstay);
  imm("t8");
  priority("t8",2);
  probval("t8",1);
  imm("no_ch_cdma");
  priority("no_ch_cdma",1);
  probval("no_ch_cdma",1);
  imm("no_ch_IEEE");
  priority("no_ch_IEEE",1);
  probval("no_ch_IEEE",1);
  imm("no__ch_cdma");
  priority("no__ch_cdma",1);
  probval("no__ch_cdma",1);
  imm("no__ch__cdma");
  priority("no__ch__cdma",1);
  probval("no__ch__cdma",1);
  imm("outof_hotspot");
  priority("outof_hotspot",1);
  probval("outof_hotspot",pout);
  imm("in_hotspot");
  priority("in_hotspot",1);
  probval("in_hotspot",pin);
  imm("no__ch_IEEE");
  priority("no__ch_IEEE",1);
  probval("no__ch_IEEE",1);
  imm("free_ch_IEEE");
  priority("free_ch_IEEE",2);
  probval("free_ch_IEEE",1);
  imm("t");
  priority("t",2);
  probval("t",1);
  imm("free_ch_cdma");
  priority("free_ch_cdma",2);
  probval("free_ch_cdma",1);
  imm("free_ch_c");
  priority("free_ch_c",2);
  probval("free_ch_c",1);
  /* Timed Transitions */ 
  ratedep("v",v,"user_cdma");
  rateval("lam_h_i",1.0);
  useparm("lam_h_i","lh");
  rateval("lam_c_w",1.0);
  useparm("lam_c_w","lv1");
  rateval("lam_w_c",1.0);
  useparm("lam_w_c","lv2");
  ratedep("mu_w",u,"user_ieee");
  ratedep("mu_c",u,"user_cdma");
  rateval("lam",l);

  /*  ======  ARC ====== */ 
  /* Input Arcs */ 
  iarc("outof_hotspot","P1");
  iarc("in_hotspot","P1");
  iarc("vehicular","P4");
  iarc("nonvehicular","P4");
  iarc("RT","P5");
  iarc("NRT","P5");
  iarc("mu_w","user_ieee");
  iarc("stay","P8");
  iarc("moveout","P8");
  iarc("no__ch_cdma","P9");
  iarc("t8","P9");
  iarc("t8","resource_cdma");
  iarc("free_ch_c","P10");
  iarc("no__ch__cdma","P10");
  iarc("free_ch_c","resource_cdma");
  iarc("free_ch_cdma","resource_cdma");
  iarc("free_ch_cdma","P11");
  iarc("t","P13");
  iarc("t","resource_ieee");
  iarc("no_ch_cdma","P11");
  iarc("no_ch_IEEE","P13");
  iarc("no__ch_IEEE","P12");
  iarc("free_ch_IEEE","P12");
  iarc("free_ch_IEEE","resource_ieee");
  iarc("lam_w_c","user_ieee");
  iarc("lam_c_w","user_cdma");
  iarc("lam_c_w","resource_ieee");
  iarc("mu_c","user_cdma");
  iarc("v","user_cdma");
  iarc("lam_h_i","resource_cdma");
  iarc("lam_w_c","resource_cdma");
  /* Output Arcs */ 
  oarc("lam","P1");
  oarc("mu_c","resource_cdma");
  oarc("in_hotspot","P4");
  oarc("nonvehicular","P5");
  oarc("mu_w","resource_ieee");
  oarc("RT","P8");
  oarc("outof_hotspot","P9");
  oarc("t8","user_cdma");
  oarc("vehicular","P10");
  oarc("free_ch_c","user_cdma");
  oarc("moveout","P11");
  oarc("stay","P12");
  oarc("free_ch_cdma","user_cdma");
  oarc("NRT","P13");
  oarc("t","user_ieee");
  oarc("free_ch_IEEE","user_ieee");
  oarc("lam_w_c","resource_ieee");
  oarc("lam_c_w","resource_cdma");
  oarc("lam_c_w","user_ieee");
  oarc("v","resource_cdma");
  oarc("lam_h_i","user_cdma");
  oarc("lam_w_c","user_cdma");
  /* Inhibtor Arcs */ 
  mharc("t8","user_cdma",2);
  mharc("free_ch_c","user_cdma",2);
  mharc("free_ch_cdma","user_cdma",2);

  /* === BIND PARAM VARIABLES === */
  bind("lh",lh);
  bind("lv1",lv1);
  bind("lv2",lv2);
} 

/* REWARD Functions */ 
double r4 () {
return(mark("user_cdma")*10+mark("user_ieee")*0.5);
}
double BN () {
if(mark("resource_cdma")<=1)
return(1.0);
else
return(0.0);
}
double BH () {
if(mark("resource_cdma")==0)
return(1.0);
else
return(0.0);
}
double thu () {
return(mark("user_cdma")*9.6+mark("user_ieee")*14.6);
}
double BNH () {
if(mark("resource_ieee")==0)
return(1.0);
else
return(0.0);
}
double LC () {
return(mark("user_cdma")/3.0);
}
double LW () {
return(mark("user_ieee")/9.0);
}


/* ======= DEFINITION OF THE FUNCTIONS ====== */

int assert() { 

} 

void ac_init() { 
/* Information on the net structure */ 
pr_net_info();

} 

void ac_reach() { 
/* Information on the reachability graph */ 
pr_rg_info();

} 


double outFunc0() {
  return(mark("P1"));
}
double outFunc1() {
  return(mark("P4"));
}
double outFunc2() {
  return(mark("P5"));
}
double outFunc3() {
  return(mark("P8"));
}
double outFunc4() {
  return(mark("P9"));
}
double outFunc5() {
  return(mark("P10"));
}
double outFunc6() {
  return(mark("P11"));
}
double outFunc7() {
  return(mark("P12"));
}
double outFunc8() {
  return(mark("P13"));
}
double outFunc9() {
  return(mark("resource_cdma"));
}
double outFunc10() {
  return(mark("resource_ieee"));
}
double outFunc11() {
  return(mark("user_cdma"));
}
double outFunc12() {
  return(mark("user_ieee"));
}

void ac_final() { 
int loop; 
int i;
  double a1,a2,a3,err1,err2,err3,m,bnu,bhu,bnhw;
  
  for (i=1; i<MAX_ITERATIONS; i++) {
    pr_value("lh", lh);
    pr_value("lv1", lv1);
    pr_value("lv2", lv2);
    bind("lh", lh);
    bind("lv1", lv1);
    bind("lv2", lv2);
    solve(INFINITY);
    bnu=expected(BN);
    bhu=expected(BH);
    bnhw=expected(BNH);
    a1 =(((l*pout*(1-bnu))+(l*pin*pmove*(1-bhu)))*a)/(1-(1-bhu)*a);
    a2=(l*pin*(pnrt*pnv+prt*pnv*pstay)*(1-bnhw)+lv1*(1-bnhw))*pnrt*pa;
    a3=(l*pout*(1-bnu)+(lh+lv2)*(1-bhu))*(pnrt*pnv+prt*pnv*pstay)*penter;
pr_value("Hho", a1);
pr_value("vh2", a2);
pr_value("vh1", a3);

    err1= fabs((lh-a1)/a1);
err2= fabs((lv1-a3)/a3);
err3= fabs((lv2-a2)/a2);
if(err1>err2)
m=err1;
else
m=err2;

if(err3>m) m=err3;
pr_value("Error", m);
    if( m < MAX_ERROR ) break;
    lh = a1;
lv1=a3;
lv2=a2;
  }

pr_value("VHO",a2+a3);
pr_expected("BN",BN);
pr_expected("BH",BH);
pr_expected("thu",thu);
pr_value("cost",expected(r4)+(a2+a3)*6.4);
pr_expected("BNH",BNH);
pr_expected("LC",LC);
pr_expected("LW",LW);
for(loop=0;loop<10;loop+=1) { 
  solve((double) loop); 
  pr_expected("Expected # of tokens of the place P1",outFunc0); 
  pr_expected("Expected # of tokens of the place P4",outFunc1); 
  pr_expected("Expected # of tokens of the place P5",outFunc2); 
  pr_expected("Expected # of tokens of the place P8",outFunc3); 
  pr_expected("Expected # of tokens of the place P9",outFunc4); 
  pr_expected("Expected # of tokens of the place P10",outFunc5); 
  pr_expected("Expected # of tokens of the place P11",outFunc6); 
  pr_expected("Expected # of tokens of the place P12",outFunc7); 
  pr_expected("Expected # of tokens of the place P13",outFunc8); 
  pr_expected("Expected # of tokens of the place resource_cdma",outFunc9); 
  pr_expected("Expected # of tokens of the place resource_ieee",outFunc10); 
  pr_expected("Expected # of tokens of the place user_cdma",outFunc11); 
  pr_expected("Expected # of tokens of the place user_ieee",outFunc12); 
} 

} 

