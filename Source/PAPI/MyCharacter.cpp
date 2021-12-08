// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"
#include "Runtime/Engine/Public/TimerManager.H"
#include"Components/InputComponent.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	bUseControllerRotationYaw = false;
	cam = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	//cam->AttachTo(RootComponent);

	arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	arm->AttachTo(RootComponent);
	arm->TargetArmLength = 300.f;
	arm->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));

	arm->bEnableCameraLag = true;
	arm->CameraLagSpeed = 2;
	arm->CameraLagMaxDistance = 1.5f;

	arm -> bEnableCameraRotationLag = true;
	arm->CameraRotationLagSpeed = 4;
	arm->CameraLagMaxTimeStep = 1;

	cam->AttachTo(arm, USpringArmComponent::SocketName);
	jumping = false;
	JumpHeight = 600.f;

	CanDash = true;
	DashDistance = 6000.f;
	DashCooldown = 1.f;
	DashStop = 0.1f;

	
	

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyCharacter::Landed(const FHitResult& Hit)
{
	DoubleJumpCounter = 0;
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (jumping)
	{
		Jump();
	}
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::DoubleJump);
	InputComponent->BindAxis("Horizontal", this, &AMyCharacter::HorizontalMove);
	InputComponent->BindAxis("Vertical", this, &AMyCharacter::VerticalMove);
	InputComponent->BindAxis("HorizontalRot", this, &AMyCharacter::HorizontalRot);
	InputComponent->BindAxis("VerticalRot", this, &AMyCharacter::VertialRot);
	
	
	
	

	//InputComponent->BindAction("Sprint", IE_Pressed, this, &AMyCharacter::Sprint);
	//InputComponent->BindAction("Sprint", IE_Released, this, &AMyCharacter::Walk);
	InputComponent->BindAction("Dash", IE_Pressed, this, &AMyCharacter::Dash);
	
}


void AMyCharacter::VertialRot(float value) 
{
	if (value)
	{
		float temp = arm->GetRelativeRotation().Pitch + value;
		if (temp < 25 && temp >-65)
		{
			arm->AddLocalRotation(FRotator(value, 0, 0));
		}
	}
}
void AMyCharacter::CheckJump() 
{
	if (jumping)
	{
		jumping = false;
	}
	else
	{
		jumping = true;
	}
}

void AMyCharacter::DoubleJump()
{
	if (DoubleJumpCounter <= 1)
	{
		AMyCharacter::LaunchCharacter(FVector(0,0,JumpHeight),false,true);
		DoubleJumpCounter++;
	}
	
}

void AMyCharacter::Dash()
{
	if (CanDash)
	{
		GetCharacterMovement()->BrakingFrictionFactor = 0.f;

		LaunchCharacter(FVector(cam->GetForwardVector().X, cam->GetForwardVector().Y, 0).GetSafeNormal()*DashDistance, true, true);
		CanDash = false;
		GetWorldTimerManager().SetTimer(UnusedHandle, this, & AMyCharacter::StopDashing, DashStop, false);
	}
}

void AMyCharacter::StopDashing()
{
	GetCharacterMovement()->StopMovementImmediately();
	GetWorldTimerManager().SetTimer(UnusedHandle, this, &AMyCharacter::ResetDash, DashCooldown, false);
	GetCharacterMovement()->BrakingFrictionFactor = 2.f;

}

void AMyCharacter::ResetDash()
{
	CanDash = true;
}




void AMyCharacter::HorizontalRot(float value) 
{
	if (value)
	{
		AddActorLocalRotation(FRotator(0, value, 0));
	}
}

void AMyCharacter::HorizontalMove(float value) 
{
	if (value)
	{
		AddMovementInput(GetActorRightVector(), value);
	}
}

void AMyCharacter::VerticalMove(float value) 
{
	if (value) 
	{
		AddMovementInput(GetActorForwardVector(), value);
	}
}

