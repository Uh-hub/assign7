#include "MyPawn.h"
#include "EagleController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"

AMyPawn::AMyPawn()
{
	PrimaryActorTick.bCanEverTick = false;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComp->SetupAttachment(RootComponent);

	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMeshComp->SetupAttachment(CapsuleComp);

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(CapsuleComp);

	SpringArmComp->TargetArmLength = 500.0f;
	//폰 컨트롤러 회전 따라 스프링암도 회전
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);

	CameraComp->bUsePawnControlRotation = true;
	//폰 컨트롤러 회전 따라 카메라 회전
	SpringArmComp->bInheritPitch = true;
	SpringArmComp->bInheritYaw = true;
	SpringArmComp->bInheritRoll = false;



}

void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (AEagleController* PlayerController = Cast<AEagleController>(GetController()))
		{
			if(PlayerController->MoveForward)
			{
				EnhancedInput->BindAction(
					PlayerController->MoveForward,
					ETriggerEvent::Triggered,
					this,
					&AMyPawn::MoveForward
				);
			}
			if (PlayerController->MoveRight)
			{
				EnhancedInput->BindAction(
					PlayerController->MoveRight,
					ETriggerEvent::Triggered,
					this,
					&AMyPawn::MoveRight
				);
			}
			if (PlayerController->Look)
			{
				EnhancedInput->BindAction(
					PlayerController->Look,
					ETriggerEvent::Triggered,
					this,
					&AMyPawn::Look
				);
			}
		}
	}	

}

void AMyPawn::MoveForward(const FInputActionValue& value)
{
	if (!Controller) return;

	const float MoveFInput = value.Get<float>();

	if (!FMath::IsNearlyZero(MoveFInput))
	{
		float Speed = 300.0f;
		FRotator ControlRotation = Controller->GetControlRotation();

		FVector ForwardDirection = FRotationMatrix(ControlRotation).GetUnitAxis(EAxis::X);

		FVector MoveOffset = ForwardDirection * MoveFInput * Speed * GetWorld()->GetDeltaSeconds();

		GetRootComponent()->AddLocalOffset(MoveOffset, true);
	}
	
}

void AMyPawn::MoveRight(const FInputActionValue& value)
{
	if (!Controller) return;

	const FVector2D MoveRInput = value.Get<FVector2D>();

	if (!FMath::IsNearlyZero(MoveRInput.Y))
	{
		float Speed = 300.0f;
		FVector MoveOffset = GetActorRightVector() * MoveRInput.Y * Speed * GetWorld()->GetDeltaSeconds();
		GetRootComponent()->AddLocalOffset(MoveOffset, true);
	}
}


void AMyPawn::Look(const FInputActionValue& value)
{
	FVector2D LookInput = value.Get<FVector2D>();
	if (!FMath::IsNearlyZero(LookInput.X))
	{
		
		FRotator NewRotation = GetActorRotation();
		NewRotation.Yaw += LookInput.X * 1.0f;  
		SetActorRotation(NewRotation);
	}

	if (!FMath::IsNearlyZero(LookInput.Y))
	{
		
		FRotator NewControlRotation = GetControlRotation();
		NewControlRotation.Pitch = FMath::Clamp(NewControlRotation.Pitch - LookInput.Y * 2.0f, -80.0f, 80.0f);
		GetController()->SetControlRotation(NewControlRotation);
	}

}


void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}


void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

