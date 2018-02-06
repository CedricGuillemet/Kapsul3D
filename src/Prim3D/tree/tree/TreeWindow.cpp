#include <windows.h>

#pragma warning( disable : 4786 ) 
#pragma warning( disable : 4305 ) 

#include <strstream>
using std::ostrstream;

#include <thigs/Random.h>
Random random;

#include <GL/gl.h> 

#include <thunk/thunks.h>

#include <strstream>
using std::strstream;
#include <util/util.h>
#include <thigs/util.h>
#include <thigs/Color.h>

#include "TreeWindow.h"

static const float PI = 3.141592653589f;

static const float TO_RAD = PI/180.0f;

TreeWindow::TreeWindow(const Ptr<WindowClass>& wc, 
		       const string& an, 
		       bool fullscreen) 
  : GLWindow(wc, an, fullscreen),
    one_frame(false),
    x(0), y(0), 
    eye(0.0f, 1.0f, 7.0f),
    heading(0.0f),
    pitch(17.0f),
    dh(0.0f),
    dp(0.0f),
    forward(false),
    backward(false),
    up(false),
    down(false),
    left(false),
    right(false),
    velocity(0.0f),
    frame_count(0),
	framecounter(0),
    last_time(GetTickCount()),
    elapsed(0),
    time_frames(10),
    overlay_focus(false),
    overlay_flag(true),
    wireframe_flag(false),
    left_mouse(false),
    day(false),
	tl_test(false),
	fill_test(false),
    leaf_texture_index(0),
    width(0),
    height(0),
    dt(1.0/20.0),
    ground_size(10.0),
    ground(10.0),
    light_count(4) {


  ground.setDay(false);
  sky.setDay(false);

  Ptr<Image> bark_image = readPNGResource("bark");
  Ptr<Image> sky_day_image = readPNGResource("sky_day");
  Ptr<Image> sky_night_image = readPNGResource("sky_night");
  Ptr<Image> ground_image = readPNGResource("ground");

  Ptr<Image> money_image = readPNGResource("money");;
  Ptr<Image> money_back_image = readPNGResource("money_back");;

  Ptr<Image> leaf_image = readPNGResource("leaf");;
  Ptr<Image> leaf_back_image = readPNGResource("leaf_back");;

  if (bark_image) {
    bark_texture = new Texture(bark_image);
    tree.setBarkTexture(bark_texture);
  }

  if (leaf_image) {
    leaf_textures.push_back(new Texture(leaf_image));
    tree.setLeafTexture(leaf_textures[0]);
  }
  if (leaf_back_image) {
    leaf_back_textures.push_back(new Texture(leaf_back_image));
    tree.setLeafBackTexture(leaf_back_textures[0]);
  } else {
    leaf_back_textures.push_back(0);
  }    

  if (money_image) {
    leaf_textures.push_back(new Texture(money_image));
  }

  if (money_back_image) {
    leaf_back_textures.push_back(new Texture(money_back_image));
  } else {
    leaf_back_textures.push_back(0);
  }

  if (sky_day_image) {
    sky_day_texture = new Texture(sky_day_image);
    sky.setDayTexture(sky_day_texture);
  }
  if (sky_night_image) {
    sky_night_texture = new Texture(sky_night_image);
    sky.setNightTexture(sky_night_texture);
  }

  if (ground_image) {
    ground_texture = new Texture(ground_image);
    ground.setTexture(ground_texture);
  }

  Ptr<Image> label_depth_image = readPNGResource("label_depth");
  if (label_depth_image) label_depth_texture = new Texture(label_depth_image);
  depth_picture = new Picture(label_depth_texture);
    
  Ptr<Image> label_balance_image = readPNGResource("label_balance");
  if (label_balance_image) label_balance_texture = new Texture(label_balance_image);
  balance_picture = new Picture(label_balance_texture);
    
  Ptr<Image> label_twist_image = readPNGResource("label_twist");
  if (label_twist_image) label_twist_texture = new Texture(label_twist_image);
  twist_picture = new Picture(label_twist_texture);
    
  Ptr<Image> label_spread_image = readPNGResource("label_spread");
  if (label_spread_image) label_spread_texture = new Texture(label_spread_image);
  spread_picture = new Picture(label_spread_texture);
    
  Ptr<Image> label_leaf_size_image = readPNGResource("label_leaf_size");
  if (label_leaf_size_image) label_leaf_size_texture = new Texture(label_leaf_size_image);
  leaf_size_picture = new Picture(label_leaf_size_texture);

  Ptr<Image> label_branch_size_image = readPNGResource("label_branch_size");
  if (label_branch_size_image) label_branch_size_texture = new Texture(label_branch_size_image);
  branch_size_picture = new Picture(label_branch_size_texture);

  Ptr<Image> label_character_image = readPNGResource("label_fullness");
  if (label_character_image) label_character_texture = new Texture(label_character_image);
  character_picture = new Picture(label_character_texture);

  Ptr<Image> logo_image = readPNGResource("nvidia");
  if (logo_image) logo_texture = new Texture(logo_image);
  logo_picture = new Picture(logo_texture);

  task = closure0(this, &TreeWindow::draw);
  
  leaf_size_slider = new Slider(0.5, 5.0, 2.0);
  branch_size_slider = new Slider(0.01, 0.5, 0.1);
  threshhold_slider = new Slider(0.0, 1.0, 0.5);
  twist_slider = new Slider(0.0, 180.0, 60.0);
  branch_slider = new Slider(0.0, 1.0, 0.7);
  branch_bias_slider = new Slider(0.0, 1.0, 0.75);
  branch_noise_slider = new Slider(0.0, 1.0, 0.5);


  overlay.addThidget(leaf_size_slider);
  overlay.addThidget(branch_size_slider);
  overlay.addThidget(threshhold_slider);
  overlay.addThidget(twist_slider);
  overlay.addThidget(branch_slider);
  overlay.addThidget(branch_bias_slider);
  overlay.addThidget(branch_noise_slider);

  overlay.addThidget(depth_picture);
  overlay.addThidget(balance_picture);
  overlay.addThidget(twist_picture);
  overlay.addThidget(spread_picture);
  overlay.addThidget(leaf_size_picture);
  overlay.addThidget(branch_size_picture);
  overlay.addThidget(character_picture);
  overlay.addThidget(logo_picture);

  /* Shouldn't have to explicity specify closure1 template
     parameters. Seems MSVC++6 (service pack 3) is inferring them
     incorrectly. */

  leaf_size_slider->setThunk(closure1<Tree,float,Void>(&tree, &Tree::setLeafSize));
  branch_size_slider->setThunk(closure1<Tree,float,Void>(&tree, &Tree::setBranchSize));

  threshhold_slider->setThunk(closure1<TreeWindow, float, Void>(this, &TreeWindow::setThreshhold));
  twist_slider->setThunk(closure1<Tree,float,Void>(&tree, &Tree::setTwist));
  branch_slider->setThunk(closure1<Tree, float, Void>(&tree, &Tree::setBranch));
  branch_bias_slider->setThunk(closure1<Tree,float,Void>(&tree, &Tree::setBranchBias));
  branch_noise_slider->setThunk(closure1<Tree,float,Void>(&tree, &Tree::setBranchNoise));


  depth_picture->setPos(0, 150, 260, 275);
  threshhold_slider->setPos(0, 150, 240, 260);

  balance_picture->setPos(0, 150, 220, 235);
  branch_slider->setPos(0, 150, 200, 220);

  twist_picture->setPos(0, 150, 180, 195);
  twist_slider->setPos(0, 150, 160, 180);

  spread_picture->setPos(0, 150, 140, 155);
  branch_bias_slider->setPos(0, 150, 120, 140);

  leaf_size_picture->setPos(0, 150, 100, 115);
  leaf_size_slider->setPos(0, 150, 80, 100);

  branch_size_picture->setPos(0, 150, 60, 75);
  branch_size_slider->setPos(0, 150, 40, 60);

  character_picture->setPos(0, 150, 20, 35);
  branch_noise_slider->setPos(0, 150, 0, 20);

  logo_picture->setPos(540, 640, 0, 30);

  /* more trees */

  tree_poses.push_back(TreePos(0.0f, 0.0f, 0.0f));
  
}


TreeWindow::~TreeWindow() {

  WindowClass::removeTask(task);
}


Void TreeWindow::setThreshhold(const float& t) {

  float u = 1.0 - t;

  u = u*u*u*u;

  float max = 0.5;
  float min = 0.03;

  threshhold = (max-min)*u + min;
  tree.setThreshhold(threshhold);

  return nothing;
}

void TreeWindow::setOneFrame() {
  one_frame = true;
}


LRESULT CALLBACK TreeWindow::callback(HWND hwnd, 
				    UINT iMsg, 
				    WPARAM wParam, 
				    LPARAM lParam) {
		
  RECT rect;

 
  switch (iMsg) {

  case WM_KEYDOWN:{
	  if(!test_flag) //disable keyboard
    switch (wParam) {

    case VK_ESCAPE:
      return GLWindow::callback(hwnd, WM_CLOSE, 0, 0);

    case VK_ADD:
      {
	for (int i=0; i<100; ++i) {
	  // give it a hundred tries, then give up
	  if (addTree()) return 0;
	}
      }
      return 0;

    case VK_SUBTRACT:
      subtractTree();
      return 0;

    case 'H':
      {
	ostrstream message;
	message << "W: wireframe\n"
		<< "S: stats\n"
		<< "U: user interface on/off\n"
		<< "C: new random noise for branch size (character)\n"
		<< "L: switch leaves\n"
		<< "D: day\n"
		<< "N: night\n"
		<< "1 thru 8: number of fireflies\n"
		<< "arrows: move left/right/up/down\n"
		<< "left mouse: move forward\n"
		<< "right mouse: move backward\n"
		<< "both: look around\n"
		<< "esc: exit\n"
		<< '\0';
	char* s = message.str();
	showInfo(s);
	delete [] s;
	return 0;
      }

    case 'W':
      wireframe_flag = !wireframe_flag;
      return 0;

    case 'U':
      overlay_flag = !overlay_flag;
      return 0;

    case 'L':
	
      if (leaf_textures.size()>0) {
	if (++leaf_texture_index>=leaf_textures.size()) {
	  leaf_texture_index = 0;
	}
	tree.setLeafTexture(leaf_textures[leaf_texture_index]);
	tree.setLeafBackTexture(leaf_back_textures[leaf_texture_index]);
      }
      return 0;

    case 'C':
      tree.newCharacter();
      return 0;

    case 'D':
      setDay();
      return 0;

    case '1':
      setNight(1);
      return 0;

    case '2':
      setNight(2);
      return 0;

    case '3':
      setNight(3);
      return 0;

    case '4':
      setNight(4);
      return 0;

    case '5':
      setNight(5);
      return 0;

    case '6':
      setNight(6);
      return 0;

    case '7':
      setNight(7);
      return 0;

    case '8':
      setNight(8);
      return 0;

    case 'N':
      setNight(light_count);
      return 0;

    case 'S':
      {
	float seconds = float(elapsed)/1000;
	float fps = float(time_frames)/seconds;
	int polygons = 
	  tree.leaves->getPolygonCount() + 
	  tree.branches->getPolygonCount() +
	  ground.getPolygonCount();
	ostrstream message;
	message << "frames per second: " << fps << '\n'
		<< "leaves: " << tree.leaves->getLeafCount() << '\n'
		<< "branches: " << tree.branches->getBranchCount() << '\n'
		<< "polygons per frame: " << polygons << '\n'
		<< "polygons per second: " << (polygons*fps) << '\000';
	char* s = message.str();
	showInfo(s);
	delete [] s;
	return 0;
      }

    case VK_RIGHT:
      right = true;
      return 0;

    case VK_LEFT:
      left = true;
      return 0;

    case VK_UP:
      up = true;
      return 0;

    case VK_DOWN:
      down = true;
      return 0;

    }//end wParam switch
    break;
  }//end WM_KEYDOWN case
  case WM_KEYUP:
    switch (wParam) {

    case VK_RIGHT:
      right = false;
      return 0;

    case VK_LEFT:
      left = false;
      return 0;

    case VK_UP:
      up = false;
      return 0;

    case VK_DOWN:
      down = false;
      return 0;
    }
    break;

  case WM_SIZE:
    GetClientRect(hwnd, &rect);
    reshapeViewport(rect.right, rect.bottom);
    return 0;

  case WM_ACTIVATE:
    {
      WORD fActive = LOWORD(wParam);           // activation flag 
      switch (fActive) {
      case WA_CLICKACTIVE:
      case WA_ACTIVE:
	WindowClass::addTask(task);
	break;
      case WA_INACTIVE:
	WindowClass::removeTask(task);
	break;
      }
    }
  return 0;

  case WM_PAINT:
    draw();
    break;
  }

  assert((hwnd==this->hwnd) || (this->hwnd==0));
  return GLWindow::callback(hwnd, iMsg, wParam, lParam);
}


Void TreeWindow::draw() {

  tick();

  context->grab();

	//set a 30 second timer.  exit when time is elapesed
  if(framecounter == 5){
		start_timer = clock();
		}
	if(framecounter == 1005 && test_flag == true)
	{ 
		ShowCursor(true);
		sendResults();
	}
  //end timer code


  if(tl_test)
	  getTLPath();
  if(fill_test)
	  getFillPath();

  if (wireframe_flag) {
    glPolygonMode(GL_FRONT, GL_LINE);
    glPolygonMode(GL_BACK, GL_LINE);
  } else {
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_FILL);
  }

  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  double aspect = double(width)/double(height);
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity(); 
  const float s = 0.05;
  glFrustum(-s * aspect, s * aspect, -s, s, 0.1, 1000.0 );
  glDepthRange(0.0, 20.0);
  glMatrixMode( GL_MODELVIEW ); 

  glLoadIdentity();

  if (day) {
    daylight.setPosition(1.0, 1.0, 0.5, 0.0);
    daylight.setAmbient(0.0, 0.0, 0.0, 0.0);
    daylight.setDiffuse(1.0, 1.0, 1.0, 1.0);
    daylight.apply();
  }

  velocity = velocity * 0.90;
  
  if (forward || backward) {
    velocity = velocity + (forward?0.1f:0.0f) + (backward?-0.1f:0.0f);
    if(test_flag){
		dh = 0;
		dp = 0;}
	else{
	dh = float(x)-float(width)/2.0f;
    dp = -(float(y)-float(height)/2.0f);
	}
  } else {
    dp = dp * 0.8;

    float to_h = atan2f(-eye[0], eye[2]) * 180.0/PI;
    dh = (to_h - heading);
    while (dh>180.0f) dh -= 360.0f;
    while (dh<=-180.0f) dh += 360.0f;
    dh *= 20.0f;
  }

  heading += dh*dt*0.05;
  pitch += dp*dt*0.05;

  float h = heading*TO_RAD;
  float p = pitch*TO_RAD;
  float sh = sinf(h);
  float ch = cosf(h);
  float sp = sinf(p);
  float cp = cosf(p);
    
  Vec3<float> forward_vec(sh*cp, sp ,-ch*cp);
  eye = eye + forward_vec * velocity * dt;

  if (right) {
    Vec3<float> right_vec(ch, 0.0f, sh);
    eye = eye + right_vec * dt;
  }
  if (left) {
    Vec3<float> right_vec(ch, 0.0f, sh);
    eye = eye + right_vec * -dt;
  }
  if (up) {
    eye[1] += dt;
  }
  if (down) {
    eye[1] -= dt;
  }

  // clamps
  if (eye[1]<0.5) eye[1] = 0.5;
  if (pitch>80.0f) pitch=80.0f;
  if (pitch<-80.0f) pitch=-80.0f;

  glRotated(pitch, -1.0, 0.0, 0.0);
  glRotated(heading, 0.0, 1.0, 0.0);

  glTranslatef(-eye[0], -eye[1], -eye[2]);

  glRotatef(-90, 1.0, 0.0, 0.0);


  for (TreePoses::iterator j=tree_poses.begin();
       j != tree_poses.end();
       ++j) {

    TreePos& tree_pos = *j;
    Firefly* fireflies = tree_pos.fireflies;

    glPushMatrix();
    glTranslated(tree_pos.x, tree_pos.y, 0.0);
    glRotatef(tree_pos.angle, 0.0, 0.0, 1.0);

    if (!day) {

      for (int i=0; i<light_count; ++i) {
	fireflies[i].move(dt);
	lights[i].setPosition(fireflies[i].pos);
	lights[i].setDiffuse(fireflies[i].c);
	lights[i].apply();
      }
    }

    tree.draw(context, wireframe_flag);
    if (!day) ground.draw(context);

    glPopMatrix();
  }

  if (day) ground.draw(context);
  sky.draw(context);

  if (!day) {
    for (TreePoses::iterator j=tree_poses.begin();
	 j != tree_poses.end();
	 ++j) {

      TreePos& tree_pos = *j;
      Firefly* fireflies = tree_pos.fireflies;

      glPushMatrix();
      glTranslated(tree_pos.x, tree_pos.y, 0.0);
      glRotatef(tree_pos.angle, 0.0, 0.0, 1.0);

      for (int i=0; i<light_count; ++i) {
	fireflies[i].draw(context);
      }
      glPopMatrix();
    }
  }



  if (overlay_flag) overlay.draw(context);

  context->swapBuffers(); 

  if (one_frame) {
    PostQuitMessage(0);
  }

  return nothing;
}



void TreeWindow::reshapeViewport(GLsizei w, GLsizei h) {

  width = w;
  height = h;

  if (width==0 || height==0) return;

  if (context) {

    context->grab();

    glViewport(0, 0, width, height);
    checkGLError("glViewport");

    //  overlay.setOrtho(width, height, 0.0, width, 0.0, height);
    overlay.setOrtho(width, height, 0.0, 640, 0.0, 480);
    checkGLError("Overlay::setOrtho");
  }
}

void TreeWindow::leftMouse(bool click) {

  if (overlay_flag && overlay_focus && !left_mouse) {

    overlay.click(click);
    return;
  }

  left_mouse = click;
  if(test_flag)
	  forward = false;
  else
  forward = left_mouse;
}


void TreeWindow::rightMouse(bool click) {
  if(test_flag)
	  backward = false;
  else
  backward = click;
}

void TreeWindow::mouse(int new_x, int new_y) {

  x = new_x;
  y = new_y;

  overlay_focus = overlay.mouse(x, y);
}


Void TreeWindow::tick() {

  DWORD t = GetTickCount();
  float new_dt = float(t-last_t)/1000.0;
  if (new_dt<1.0f) {
    // smooth it out a little bit
    if(!test_flag)
	  dt = dt * 0.7 + new_dt * 0.3;
	else
	  dt = 0.07;  
  }
  last_t = t;

  ++framecounter;

  if (++frame_count==time_frames) {
    frame_count = 0;
    DWORD time = GetTickCount();
    elapsed = time - last_time;
    last_time = time;
  }
  return nothing;
}
      
void TreeWindow::init() {

  GLWindow::init();

  context = getContext();

  context->grab();

  reshapeViewport(width, height);

  tick();

  glClearDepth( 1.0 );
  glEnable(GL_DEPTH_TEST);
  //  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  //  glEnable(GL_RESCALE_NORMAL);
  glEnable(GL_NORMALIZE);

  Light::setGlobalAmbient(Vec4<float>(0.0, 0.0, 0.0, 0.0));

  for (int i=0; i<max_lights; ++i) {
    lights[i].setAmbient(0.0, 0.0, 0.0);
    lights[i].setAttenuation(0.0, 1.0, 0.1);
  }

}


void TreeWindow::setDay() {

  day = true;
  for (int i=0; i<light_count; ++i) lights[i].disable();
  sky.setDay(day);
  ground.setDay(day);
}


void TreeWindow::setNight(int n) {

  light_count = n;
  day = false;
  for (int i = light_count; i<max_lights; ++i) lights[i].disable();
  daylight.disable();
  sky.setDay(day);
  ground.setDay(day);
}

void TreeWindow::setBench(bool is_bench, int depth, bool fill, int lites)
{
	
	if(is_bench == true){
		ShowCursor(false);
		test_flag = true;
		//fullscreen = true;
		setNight(lites);
	}
	else
		test_flag = false;
	if(is_bench == true && fill == true){
		fill_test = true;
		tl_test = false;
		tree.setLeafSize(5.0);
		tree.setBranchNoise(0.5);
		tree.setBranch(0.7);
		tree.setBranchBias(0.7);
		tree.setTwist(60.0);

		}
	else if(is_bench == true && fill == false){
		tl_test = true;
		fill_test = false;}
	//else{
	//	tl_test = false;
	//	fill_test = false;
	//}

	switch(depth){
	case 1:
		setThreshhold(0.1);
		break;
	case 2:
		setThreshhold(0.2);
		break;
	case 3:
		setThreshhold(0.3);
		break;
	case 4:
		setThreshhold(0.4);
		break;
	case 5:
		setThreshhold(0.5);
		break;
	case 6:
		setThreshhold(0.6);
		break;
	case 7:
		setThreshhold(0.7);
		break;
	case 8:
		setThreshhold(0.8);
		break;
	case 9:
		setThreshhold(0.9);
		break;
	case 10:
		setThreshhold(1.0);
		break;
	default:
		setThreshhold(0.5);
	}

}


void TreeWindow::getTLPath()
{
	if (test_flag){ //benchmark flag is true
	  //left = true;
	  overlay_flag = false;
	}
	


  if(framecounter <= 70)
	  forward = true;
  else
	  forward = false;
  
  if(framecounter > 150 && framecounter <= 250)
	  right = true;
  else
	  right = false;
  if(framecounter > 290 && framecounter <= 330)
	  backward = true;
  else 
	  backward = false;
  if(framecounter > 350)
	  left = true;
}

void TreeWindow::getFillPath()
{
	if (test_flag){ //benchmark flag is true
	 	  overlay_flag = false;
	}


	if(framecounter < 70)
	forward = true;
	else
		forward = false;
	if(framecounter >=100 && framecounter <= 350)
		right = true;
	else
		right = false;
	if(framecounter >= 400 && framecounter <= 480){
		forward = true;
		}
	else if(framecounter > 480){
		forward = false;
		}
	if(framecounter >=440 && framecounter <=470)
		down = true;
	else
		down = false;

	if(framecounter > 510 && framecounter < 710){
		left = true;}
	else{
		left = false;}
	if(framecounter > 720 && framecounter < 780)// && framecounter < 770)
		forward = true;
	if(framecounter > 780)
		right = true;
	if(framecounter > 985)
		right = false;
	//if(framecounter > 760 && framecounter< 780)
		//down = true;
}

void TreeWindow::sendResults()
{
	end_timer = clock();
	  Timer = (double)(end_timer - start_timer) / CLOCKS_PER_SEC;
		float seconds = float(elapsed)/1000;
		float fps = float(time_frames)/seconds;
		//float dh_fps = float(framecounter)/Timer; //dh calculate fps via framecounter
		float dh_fps = 1000.0 / Timer;
		int polygons = 
	      tree.leaves->getPolygonCount() + 
	      tree.branches->getPolygonCount() +
	      ground.getPolygonCount();
		ostrstream message;
		message << "frames per second: " << dh_fps << '\n'
		  << "Screen Resolution " <<GetSystemMetrics(SM_CXSCREEN)<<"x"<<GetSystemMetrics(SM_CYSCREEN) << '\n'
		  << "Timer is " << Timer << '\n'
		  << "Frame count is " << framecounter - 5 << '\n'
		  << "leaves: " << tree.leaves->getLeafCount() << '\n'
		  << "branches: " << tree.branches->getBranchCount() << '\n'
		  << "polygons per frame: " << polygons << '\n'
		  << "polygons per second: " << (polygons*fps) << '\000';
	  char* s = message.str();
	  //showInfo(s);
	  writeInfo(s);
	  delete [] s;
	  
    //SendMessage(hwnd, WM_CLOSE, 0, 0);
	GLWindow::callback(hwnd, WM_CLOSE, 0, 0);
}


bool TreeWindow::addTree() {

  static float scale = sky.radius-ground_size;
  static float miss = ground_size;
  static float cone = 60.0f;

  float r = random * random * scale;
  float h = (heading + (random * cone - cone/2.0f)) * pi / 180;
  //  float h = heading * pi / 180;

  float y = cosf(h) * r;
  float x = sinf(h) * r;

  Vec2f p1(x, y);

  for (TreePoses::iterator i = tree_poses.begin();
       i != tree_poses.end();
       ++i) {

    Vec2f p2((*i).x, (*i).y);
    Vec2f d = p2 - p1;
    if (dot(d, d)<(miss*miss)) return false;
  }

  tree_poses.push_back(TreePos(x, y, random*360.0));
  return true;
}


void TreeWindow::subtractTree() {

  if (tree_poses.size()>1) {
    tree_poses.pop_back();
  }

}

