// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiPlayer_CharacterBase.h"
#include "Port_FPS/Character/Player/PlayerState/PlayerStateBase.h"
#include "Port_FPS/Character/Player/PlayerState/Aim_PlayerUpper_StateBase.h"
#include "Port_FPS/Character/Player/PlayerState/Standing_PlayerDown_StateBase.h"
#include "Port_FPS/Character/Player/PlayerState/MultiPlayer_State/Prone_M_PlayerDown_StateBase.h"


AMultiPlayer_CharacterBase::AMultiPlayer_CharacterBase()
{
	//bReplicates = true;
	SetReplicates(true);
	SetReplicateMovement(true);
	BodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BODY"));
	BodyMesh->SetupAttachment(RootComponent);
	BodyMesh->SetRelativeLocation(FVector(-20.0f, 0.0f, -97.0f));
	BodyMesh->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));
	BodyMesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	BodyMesh->SetCollisionProfileName("CharacterMesh");
	
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>LEGBODY_SKELETALMESH(TEXT("SkeletalMesh'/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'"));
	if (LEGBODY_SKELETALMESH.Succeeded()) { BodyMesh->SetSkeletalMesh(LEGBODY_SKELETALMESH.Object); }
	static ConstructorHelpers::FClassFinder<UAnimInstance>LEGBODY_ANIMBP(TEXT("AnimBlueprint'/Game/Player/Animation/Body/PlayerBody_AnimBP.PlayerBody_AnimBP_C'"));
	if (LEGBODY_ANIMBP.Succeeded()) { BodyMesh->SetAnimInstanceClass(LEGBODY_ANIMBP.Class); }
	
	SpringArm->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));

}

void AMultiPlayer_CharacterBase::BeginPlay()
{
	Super::BeginPlay();

	BodyMesh->SetOwnerNoSee(true);
	BodyMesh->SetCastShadow(true);
	BodyMesh->bCastHiddenShadow = true;

	SetStateDownN(NewObject<UStanding_PlayerDown_StateBase>(this, UStanding_PlayerDown_StateBase::StaticClass()));
	SetStateUpperN(NewObject<UAim_PlayerUpper_StateBase>(this, UAim_PlayerUpper_StateBase::StaticClass()));
	/*if (!HasAuthority() && IsLocallyControlled()) {
		Server_Update_PlayerDownState(NewObject<UStanding_PlayerDown_StateBase>(this, UStanding_PlayerDown_StateBase::StaticClass()));
		Server_Update_PlayerUpperState(NewObject<UAim_PlayerUpper_StateBase>(this, UAim_PlayerUpper_StateBase::StaticClass()));
	}*/
	StateDownNClass = GetStateDownN()->GetState();
	StateUpperNClass = GetStateUpperN()->GetState();
	GetStateDownN()->StateStart(this);
	GetStateUpperN()->StateStart(this);
	
	//SetStateDownN(NewObject<UProne_M_PlayerDown_StateBase>(this, UProne_M_PlayerDown_StateBase::StaticClass()));
	//GetStateDownN()->StateStart(this);
}

void AMultiPlayer_CharacterBase::TurnAtRate(float Rate)
{
	//Super::TurnAtRate(Rate);
	AimDirRight = Rate;
	if (IsLocallyControlled()) {
		
	}
	//GetStateDownN()->TurnAtRate(this, 1.0f);
}

void AMultiPlayer_CharacterBase::LookUpAtRate(float Rate)
{
	//Super::LookUpAtRate(Rate);
	AimDirForward = Rate;
	if (IsLocallyControlled()) {
		
	}
	//GetStateDownN()->LookUpAtRate(this, 1.0f);
}

void AMultiPlayer_CharacterBase::PlayerJump()
{
	Super::PlayerJump();
}

void AMultiPlayer_CharacterBase::PlayerCrouch()
{
	Super::PlayerCrouch();
	
}

void AMultiPlayer_CharacterBase::MoveForward(float Value)
{
	Super::MoveForward(Value);
}

void AMultiPlayer_CharacterBase::MoveRight(float Value)
{
	Super::MoveRight(Value);
}

void AMultiPlayer_CharacterBase::PlayerInputTest()
{
	if (HasAuthority()) {
		UE_LOG(LogTemp, Warning, TEXT("Server_: PlayerInputTest"));
		testd++;
		UE_LOG(LogTemp, Warning, TEXT("server_Update: %s testd %f"), *GetName(), testd);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Cla_: PlayerInputTest"));
		//Server_PlayerRotation(PlayerRotationYawSpeed, PlayerRotationYaw);
		UE_LOG(LogTemp, Warning, TEXT("cla_Update: %s testd %f"), *GetName(), testd);
	}
}

bool AMultiPlayer_CharacterBase::Server_Update_PlayerMove_Validate(FVector Dir, float DirInput)
{
	return true;
}
void AMultiPlayer_CharacterBase::Server_Update_PlayerMove_Implementation(FVector Dir, float DirInput)
{
	InputDir = DirInput;
	MoveDir = Dir;
	AddMovementInput(Dir, FMath::GetMappedRangeValueClamped(FVector2D(0.0f, 1.0f), FVector2D(0.0f, PlayerSpeed), DirInput) * GetWorld()->DeltaTimeSeconds);
	//Move(GetWorld()->DeltaTimeSeconds);
}

bool AMultiPlayer_CharacterBase::Server_PlayerRotation_Validate(float PlayerRotationSpeed, float PlayerYaw)
{
	return true;
}
void AMultiPlayer_CharacterBase::Server_PlayerRotation_Implementation(float PlayerRotationSpeed, float PlayerYaw)
{
	PlayerRotationYaw = PlayerYaw;
	PlayerRotationYawSpeed = PlayerRotationSpeed;
}

bool AMultiPlayer_CharacterBase::Server_Update_PlayerDownState_Validate(UPlayerDown_StateBase* state)
{
	return true;
}
void AMultiPlayer_CharacterBase::Server_Update_PlayerDownState_Implementation(UPlayerDown_StateBase* state)
{
	SetStateDownN(state);
}

bool AMultiPlayer_CharacterBase::Server_Update_PlayerUpperState_Validate(UPlayerUpper_StateBase* state)
{
	return true;
}

void AMultiPlayer_CharacterBase::Server_Update_PlayerUpperState_Implementation(UPlayerUpper_StateBase* state)
{
	SetStateUpperN(state);
}

void AMultiPlayer_CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//GetStateDownN()->StateUpdate(this);
	//GetStateUpperN()->StateUpdate(this);

	GetStateDownN()->TurnAtRate(this, AimDirRight);
	GetStateDownN()->LookUpAtRate(this, AimDirForward);
	//UE_LOG(LogTemp, Warning, TEXT("server_Update: %s AimDirRight %f"), *GetName(), DeltaTime);
	if (HasAuthority()) { // 플레이어 전체 회전 (서버)
		if (IsLocallyControlled()) {
			Move(DeltaTime);
		}
		else {
		}
		SetActorRelativeRotation(FRotator(0.0f, PlayerRotationYaw, 0.0f));
		PitchAndYaw();
		//UE_LOG(LogTemp, Warning, TEXT("server_Update: %s PlayerRotationYaw %f"), *GetName(), PlayerRotationYaw);
	}
	else { // (클라이언트)
		if (IsLocallyControlled()) {
			Move(DeltaTime);
			SetActorRelativeRotation(FRotator(0.0f, PlayerRotationYaw, 0.0f));
			//Server_PlayerRotation(PlayerRotationYawSpeed, PlayerRotationYaw);
			PitchAndYaw(); // 자연스럽게 하기위해 서버에서도 따로 처리하고 클라이언트에서도(주인만) 따로 처리한다 대신 서버에서는 다른 클라이언트에게 복제하여 전달.
		}
		else {
		}
		//UE_LOG(LogTemp, Warning, TEXT("cla_Update: %s PlayerRotationYaw %f"), *GetName(), PlayerRotationYaw);
	}
}

void AMultiPlayer_CharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//PlayerInputComponent->BindAxis("Turn", this, &AMultiPlayer_CharacterBase::TurnAtRate);
	//PlayerInputComponent->BindAxis("LookUp", this, &AMultiPlayer_CharacterBase::LookUpAtRate);

	PlayerInputComponent->BindAction("Testput", IE_Pressed, this, &AMultiPlayer_CharacterBase::PlayerInputTest);

}

void AMultiPlayer_CharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMultiPlayer_CharacterBase::PitchAndYaw()
{
	float Deltatime = GetWorld()->GetDeltaSeconds();
	FRotator InterpToAngle = FMath::RInterpTo(FRotator(Upper_Pitch, Upper_Yaw, 0.0f), ((GetControlRotation() - GetActorRotation()).GetNormalized()), Deltatime, 500.0f);
	Upper_Yaw = FMath::ClampAngle(InterpToAngle.Yaw, -90.0f, 90.0f);
	Upper_Yaw2 = InterpToAngle.Yaw;
	Upper_Pitch= FMath::ClampAngle(InterpToAngle.Pitch, -90.0f, 90.0f);
	
}

void AMultiPlayer_CharacterBase::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(AMultiPlayer_CharacterBase, testd, COND_SkipOwner);

	DOREPLIFETIME_CONDITION(AMultiPlayer_CharacterBase, PlayerRotationYawSpeed, COND_SkipOwner);
	DOREPLIFETIME_CONDITION(AMultiPlayer_CharacterBase, PlayerRotationYaw, COND_SkipOwner);

}
