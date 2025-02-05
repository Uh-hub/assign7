#include "MyGameMode.h"
#include "MyPawn.h"
#include "EagleController.h"

AMyGameMode::AMyGameMode() 
{
	//객체를 생성하지 않았지만 class 정보를 반환해줌
	DefaultPawnClass = AMyPawn::StaticClass();
	PlayerControllerClass = AEagleController::StaticClass();
}




