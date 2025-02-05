#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EagleController.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class ASSIGN7_API AEagleController : public APlayerController
{
	GENERATED_BODY()
	

public:
	AEagleController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	UInputMappingContext* InputMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MoveForward;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MoveRight;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* Look;

	virtual void BeginPlay() override;
};
