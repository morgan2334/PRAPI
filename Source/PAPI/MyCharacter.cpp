// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"

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
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("Horizontal", this, &AMyCharacter::HorizontalMove);
	InputComponent->BindAxis("Vertical", this, &AMyCharacter::VerticalMove);
	InputComponent->BindAxis("HorizontalRot", this, &AMyCharacter::HorizontalRot);
	InputComponent->BindAxis("VerticalRot", this, &AMyCharacter::VertialRot);
	
	InputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::CheckJump);
	InputComponent->BindAction("Jump", IE_Released, this, &AMyCharacter::CheckJump);
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

