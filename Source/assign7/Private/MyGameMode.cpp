#include "MyGameMode.h"
#include "MyPawn.h"
#include "EagleController.h"

AMyGameMode::AMyGameMode() 
{
	//��ü�� �������� �ʾ����� class ������ ��ȯ����
	DefaultPawnClass = AMyPawn::StaticClass();
	PlayerControllerClass = AEagleController::StaticClass();
}




