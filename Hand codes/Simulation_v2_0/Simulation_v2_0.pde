import processing.serial.*;
import java.awt.event.KeyEvent;
import java.io.IOException;

Serial myPort;
String data="";
//float roll, pitch;

finger activate;
finger deactivate;
int x =0;
float val = 0;
float state = 0;

void setup() {
  size(800,600);
  rectMode(CENTER);
  activate = new finger(color(255,0,0), 1.02);
  deactivate = new finger(color(255,255,255), 1);
  frameRate(30);
  myPort = new Serial(this, "COM5", 115200); // starts the serial communication
  myPort.bufferUntil('\n');
}

void draw() {
  noStroke();
  pushMatrix();
  translate(150,-20);
  //background(33);
  textSize(22);
  text("state: " + int(state) + "     Pitch: " + int(val), 240, 300);
  // Rotate the object
  //rotateX(radians(roll));
  //rotateZ(radians(-pitch));
  
  if (state == 0){
  deactivate.pinky();
  deactivate.ring();
  deactivate.middle();
  deactivate.index();
  deactivate.thumb();
  }
  else if (state == 1){
  activate.pinky();
  activate.ring();
  activate.middle();
  activate.index();
  activate.thumb();
  }
  else if (state == 2){
  deactivate.pinky();
  activate.ring();
  deactivate.middle();
  activate.index();
  deactivate.thumb();
  }
  else if (state == 3){
  deactivate.pinky();
  deactivate.ring();
  deactivate.middle();
  activate.index();
  deactivate.thumb();
  }
  else if (state == 4){
  deactivate.pinky();
  deactivate.ring();
  deactivate.middle();
  activate.index();
  activate.thumb();
  }
  else if (state == 5){
  deactivate.pinky();
  deactivate.ring();
  activate.middle();
  activate.index();
  deactivate.thumb();
  }
  
  fill(255);
  
  // 3D 0bject
  //textSize(30);  
  //fill(0, 76, 153);
  //box (386, 40, 200); // Draw box
  //textSize(25);
  //fill(255, 255, 255);
  //text("www.HowToMechatronics.com", -183, 10, 101);
  //delay(10);
  //println("ypr:\t" + angleX + "\t" + angleY); // Print the values to check whether we are getting proper values
   arc(240,width/2+20,330,350, radians(0), radians(180), CHORD); // Palm
   popMatrix();
}
// Read data from the Serial Port
void serialEvent (Serial myPort) { 
  // reads the data from the Serial Port up to the character '.' and puts it into the String variable "data".
  data = myPort.readStringUntil('\n');
  // if you got any bytes other than the linefeed:
  if (data != null) {
    data = trim(data);
    // split the string at "/"
    String items[] = split(data, '/');
    if (items.length > 1) {
      //--- Roll,Pitch in degrees
      state = float(items[0]);
      val = float(items[1]);
    }
  }
}







//finger activate;
//finger deactivate;
//int x =0;
////boolean status = false;

//void setup(){
//  size(800,600);
//  rectMode(CENTER);
//  activate = new finger(color(255,0,0), 1.02);
//  deactivate = new finger(color(255,255,255), 1);
//  frameRate(30);
//}

//void draw(){
//  noStroke();
//  //fill(38, 38, 200);
//  pushMatrix();
//  translate(150,-20);
// // if (status == false){
//  deactivate.pinky();
//  deactivate.ring();
//  deactivate.middle();
//  deactivate.index();
//  deactivate.thumb();
////  }
//  //else if (status == true){
//  //activate.pinky();
//  //activate.ring();
//  //activate.middle();
//  //activate.index();
//  //activate.thumb();
//  //}
//  fill(255);
//  arc(240,width/2+20,330,350, radians(0), radians(180), CHORD); // Palm
//  popMatrix();
//  //x+=10;
//  //if(x >= width)
//  //{
//  //  x=0;
//  //  status = !status;
//  //}
//  //text("y = " + x, 400, 300);
//}


class finger {
  color c;
  float zoom;
  
  finger(color tempC, float tempzoom) {
    c = tempC;
    zoom = tempzoom;
  }

void pinky()
{
  pushMatrix();
  //stroke(1);
  fill(c);
  //scale(zoom);
  rect(100,width/2-40,50,80);
  rect(100,width/2-125,50,80);
  arc(100,width/2-170,50,100, radians(180), radians(360), CHORD);
  popMatrix();
}

void ring()
{
  fill(c);
  rect(170,width/2-60,50,120);
  rect(170,width/2-185,50,120);
  arc(170,width/2-250,50,100, radians(180), radians(360), CHORD);
}

void middle()
{
  fill(c);
  rect(240,width/2-75,50,150);
  rect(240,width/2-230,50,150);
  arc(240,width/2-310,50,100, radians(180), radians(360), CHORD);
}

void index()
{
  fill(c);
  rect(310,width/2-65,50,130);
  rect(310,width/2-200,50,130);
  arc(310,width/2-270,50,100, radians(180), radians(360), CHORD);
}

void thumb()
{
  fill(c);
  pushMatrix();
  translate(380,width/2-60);
  rotate(radians(20));
  rect(15,-5,50,120);
  popMatrix();
  pushMatrix();
  translate(420,width/2-125);
  rotate(radians(20));
  arc(0,0,50,100, radians(180), radians(360), CHORD);
  popMatrix();
}
}
