#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

class UCapsuleComponent;
class USpringArmComponent;
class UCameraComponent;
class USkeletalMeshComponent;

struct FInputActionValue;

UCLASS()
class ASSIGN7_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:

	AMyPawn();

protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components|Capsule")
	UCapsuleComponent* CapsuleComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
	UCameraComponent* CameraComp;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category="Components|SkeletalMesh")
	USkeletalMeshComponent* SkeletalMeshComp;



	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void MoveForward(const FInputActionValue& value);
	UFUNCTION()
	void MoveRight(const FInputActionValue& value);
	UFUNCTION()
	void Look(const FInputActionValue& value);




};
