#include <bangtal.h>

TimerID timer1;
SceneID scene1;
ObjectID startButton, endButton, playButton, santa;
int santaX = 0, santaY = 500;


void endGame(bool success) {

	if (success == true) {
		showMessage("succes");
	}
	else {
		showMessage("miss");
	}
	hideObject(playButton);

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

	showObject(playButton);

	setTimer(timer1, 10.0f);
	startTimer(timer1);
}
void mouse_Callback(ObjectID object, int x, int y, MouseAction action) {
	
	if (object == endButton) {
		endGame();
	
	}else if (object == startButton){
		void startGame();
		
	
	}else if (object == playButton) {
		
		santaX = santaX + 30;
		locateObject(santa, scene1, santaX, santaY);
		
		if (santaX > 1280) {
			
			endGame(true);
		 }
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
	
	setMouseCallback(mouse_Callback);
	setTimerCallback(timer_Callback);

	scene1 = createScene("santaRace", "Images/background.png");

	startButton = createObject("Images/start.png", scene1, 590, 70, true);
	endButton = createObject("Images/end.png", scene1, 590, 20, true);
	playButton = createObject("Images/play.png", scene1, 610, 30, false);
	santa = createObject("Images/santa.png", scene1, santaX, santaY, true);

	timer1 = createTimer(10.0f);
	showTimer(timer1);

	startGame(scene1);
}