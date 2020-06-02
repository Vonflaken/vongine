#ifndef __APPGAME_H__
#define __APPGAME_H__

class AppGame
{
public:
	/**
	* Game entry point.
	*/
	bool StartGame();

	/**
	* Called when engine finished its initialization and It's ready for using by the user.
	*/
	void OnEngineLoadedCallback();
};

#endif // __APPGAME_H__
