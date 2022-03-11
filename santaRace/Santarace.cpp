#include <bangtal.h>
#include <cstdlib>

TimerID timer1;
SceneID scene1;
ObjectID startButton, endButton, santa, cloud;

int santaX = 0, santaY = 500, cloudX, cloudY;


void endGame(bool success) {

	if (success == true) {
		showMessage("배달에 성공했습니다!");
	}
	else {
		showMessage("배달을 실패했습니다 ㅠㅠ");
	}

	setObjectImage(startButton, "Images/restart.png");
	showObject(startButton);
	showObject(endButton);

	santaX = 0;
	locateObject(santa, scene1, santaX, santaY);
	stopTimer(timer1);
}
void startGame() {
	hideObject(startButton);
	hideObject(endButton);

	showMessage("방향키를 사용하여 산타를 움직을 수 있습니다!");

	setTimer(timer1, 30.0f);
	startTimer(timer1);
}
void mouse_Callback(ObjectID object, int x, int y, MouseAction action) {
	
	if (object == endButton) {
		endGame();
	
	}else if (object == startButton){
		 startGame();
	}
}
void keybord_Callback(KeyCode key, KeyState state) { 

	if (state == KeyState::KEY_PRESSED) {
		if (key == KeyCode::KEY_UP_ARROW) {
			santaY = santaY + 20;
		}
		else if (key == KeyCode::KEY_DOWN_ARROW) {
			santaY = santaY - 20;
		}
		else if (key == KeyCode::KEY_RIGHT_ARROW) {
			santaX = santaX + 20;
		}
		else if (key == KeyCode::KEY_LEFT_ARROW) {
			santaX = santaX - 20;
		}
	}
	
	locateObject(santa, scene1, santaX, santaY);

	if (santaX > 1280) {
		endGame(true);
	}else if (santaX < 0) {
		showMessage("반대로 가야합니다!");
		santaX = 0;

	}else if (santaY > 650) {
		showMessage("고도가 너무 높습니다!");
		santaY = 650;
	}else if (santaY < 300) {
		showMessage("고도가 너무 낮습니다!");
		santaY = 300;
	}
}
void timer_Callback(TimerID timer) {
	if (timer == timer1) {

		endGame(false);
	}
}



ObjectID createObject(const char* image, SceneID scene, int x, int y, bool shown) {
	
	ObjectID object = createObject(image);

	locateObject(object, scene, x, y);

	if (shown) {
		showObject(object);
	}
	return object;
}

int main(){
	setKeyboardCallback(keybord_Callback);
	setMouseCallback(mouse_Callback);
	setTimerCallback(timer_Callback);

	scene1 = createScene("santaRace", "Images/background.png");

	startButton = createObject("Images/start.png", scene1, 590, 70, true);
	endButton = createObject("Images/end.png", scene1, 590, 20, true);
	cloud = createObject("Images/cloud.png",scene1, cloudX, cloudY, true);
	santa = createObject("Images/santa.png", scene1, santaX, santaY, true);
	scaleObject(santa, 0.5f);

	timer1 = createTimer(30.0f);
	showTimer(timer1);

	startGame(scene1);
}
