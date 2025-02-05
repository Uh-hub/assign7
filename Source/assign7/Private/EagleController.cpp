#include "EagleController.h"
#include "EnhancedInputSubsystems.h"

AEagleController::AEagleController()
	:InputMappingContext(nullptr),
	MoveForward(nullptr),
	MoveRight(nullptr),
	Look(nullptr)
{
}


void AEagleController::BeginPlay()
{
    Super::BeginPlay();

    // 현재 PlayerController에 연결된 Local Player 객체를 가져옴    
    if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
    {
        // Local Player에서 EnhancedInputLocalPlayerSubsystem을 획득
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
        {
            if (InputMappingContext)
            {
                UE_LOG(LogTemp, Warning, TEXT("✅ InputMappingContext is valid:"));
                Subsystem->AddMappingContext(InputMappingContext, 0);
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("❌ InputMappingContext is nullptr! BP에서 설정 확인 필요"));
            }
        }
    }
}