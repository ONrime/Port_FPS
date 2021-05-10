// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_CharacterBase.h"
#include "Port_FPS/Character/Player/PlayerState/PlayerStateBase.h"
#include "Port_FPS/Character/Player/PlayerState/Aim_PlayerUpper_StateBase.h"
#include "Port_FPS/Character/Player/PlayerState/Standing_PlayerDown_StateBase.h"
#include "Net/UnrealNetwork.h"

APlayer_CharacterBase::APlayer_CharacterBase()
{
	//GetCapsuleComponent()->SetCollisionProfileName("");
	SetReplicates(true);
	SetReplicateMovement(true);
	//GetMesh()->SetCollisionProfileName("");
	/*static ConstructorHelpers::FObjectFinder<USkeletalMesh>FULLBODY_SKELETALMESH(TEXT("SkeletalMesh'/Game/PlayerFile/Mesh/SC_Cyborg_Soldier_V3.SC_Cyborg_Soldier_V3'"));
	if (FULLBODY_SKELETALMESH.Succeeded()) { GetMesh()->SetSkeletalMesh(FULLBODY_SKELETALMESH.Object); }
	static ConstructorHelpers::FClassFinder<UAnimInstance>FULLBODY_ANIMBP(TEXT("AnimBlueprint'/Game/PlayerFile/Animation/Body/AnimBP_Player_Down.AnimBP_Player_Down_C'"));
	if (FULLBODY_ANIMBP.Succeeded()) { GetMesh()->SetAnimInstanceClass(FULLBODY_ANIMBP.Class); }*/

	static ConstructorHelpers::FClassFinder<UAnimInstance>FULLBODY_ANIMBP(TEXT("AnimBlueprint'/Game/Player/Animation/Body/PlayerBody_AnimBP.PlayerBody_AnimBP_C'"));
	if (FULLBODY_ANIMBP.Succeeded()) { GetMesh()->SetAnimInstanceClass(FULLBODY_ANIMBP.Class); }
	bUseControllerRotationYaw = false;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 65.0f));
	SpringArm->bDoCollisionTest = true;
	SpringArm->TargetArmLength = 0.0f;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritRoll = false;
	SpringArm->bInheritYaw = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	FollowCamera->SetupAttachment(SpringArm);
	FollowCamera->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	FollowCamera->bUsePawnControlRotation = false;

	ArmMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ArmMesh"));
	ArmMesh->SetupAttachment(FollowCamera);
	ArmMesh->SetCollisionProfileName("CharacterMesh");
	ArmMesh->SetRelativeLocation(FVector(-7.0f, 0.0f, -155.0f));
	ArmMesh->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	ArmMesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	ArmMesh->SetHiddenInGame(false);
	ArmMesh->SetCastShadow(false);
	ArmMesh->bCastHiddenShadow = true;
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>ARM_SKELETALMESH(TEXT("SkeletalMesh'/Game/FirstPerson/Character/Mesh/SK_Mannequin_Arms.SK_Mannequin_Arms'"));
	if (ARM_SKELETALMESH.Succeeded()) { ArmMesh->SetSkeletalMesh(ARM_SKELETALMESH.Object); }
	static ConstructorHelpers::FClassFinder<UAnimInstance>ARM_ANIMBP(TEXT("AnimBlueprint'/Game/FirstPerson/Animations/FirstPerson_AnimBP.FirstPerson_AnimBP_C'"));
	if (ARM_ANIMBP.Succeeded()) { ArmMesh->SetAnimInstanceClass(ARM_ANIMBP.Class); }

	GetCharacterMovement()->bOrientRotationToMovement = false; // 이동방향에 맞춰서 회전을 보간해준다.(회전은 내가 바꾸기 때문에 false)	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 0.0f, 0.0f); // 회전 속도 0.0으로 초기화 (왜 했지?)
	GetCharacterMovement()->JumpZVelocity = 500.0f;
	GetCharacterMovement()->AirControl = 0.2f;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;  // 컨트롤러 방향으로 캐릭터 회전(무브먼트 기준)
	GetCharacterMovement()->MovementMode = EMovementMode::MOVE_Walking;


}

void APlayer_CharacterBase::BeginPlay()
{
	Super::BeginPlay();

	GetMesh()->HideBoneByName(FName("spine_03"), PBO_None);
	GetMesh()->SetOnlyOwnerSee(true);
	GetMesh()->SetCastShadow(false);
	ArmMesh->SetOnlyOwnerSee(true);
	IsPlayerCameraTurn = true;

	//StateDownN = NewObject<UStanding_PlayerDown_StateBase>(this, UStanding_PlayerDown_StateBase::StaticClass());
	//StateUpperN = NewObject<UAim_PlayerUpper_StateBase>(this, UAim_PlayerUpper_StateBase::StaticClass());
	/*//StateDownN = nullptr;
	//StateUpperN = nullptr;
	/*if (!HasAuthority() && IsLocallyControlled()) {
		Server_Update_PlayerDownState(NewObject<UStanding_PlayerDown_StateBase>(this, UStanding_PlayerDown_StateBase::StaticClass()));
		Server_Update_PlayerUpperState(NewObject<UAim_PlayerUpper_StateBase>(this, UAim_PlayerUpper_StateBase::StaticClass()));
	}
	StateDownNClass = StateDownN->GetState();
	StateUpperNClass = StateUpperN->GetState();
	StateDownN->StateStart(this);
	StateUpperN->StateStart(this);*/

}

void APlayer_CharacterBase::TurnAtRate(float Rate)
{
	AimDirRight = Rate;
	float Deltatime = GetWorld()->GetDeltaSeconds();
	FRotator InterpToAngle = FMath::RInterpTo(FRotator(0.0f, Upper_Yaw, 0.0f), ((GetControlRotation() - GetActorRotation()).GetNormalized()), Deltatime, 500.0f);
	Upper_Yaw = FMath::ClampAngle(InterpToAngle.Yaw, -90.0f, 90.0f);
	Upper_Yaw2 = InterpToAngle.Yaw;
	//GetStateDownN()->TurnAtRate(this, 1.0f);
	//UE_LOG(LogTemp, Warning, TEXT("Upper_Yaw Rotation: %f"), YawUpper_Yaw);
	/*AimDirRight = Rate;
	if (IsLocallyControlled()) {
		
	}
	GetStateDownN()->TurnAtRate(this, Rate);*/
}

void APlayer_CharacterBase::LookUpAtRate(float Rate)
{
	AimDirForward = Rate;
	float Deltatime = GetWorld()->GetDeltaSeconds();
	FRotator InterpToAngle = FMath::RInterpTo(FRotator(Upper_Pitch, 0.0f, 0.0f), ((GetControlRotation() - GetActorRotation()).GetNormalized()), Deltatime, 500.0f);
	FMath::ClampAngle(InterpToAngle.Pitch, -90.0f, 90.0f);
	Upper_Pitch = FMath::ClampAngle(InterpToAngle.Pitch, -90.0f, 90.0f);
	//UE_LOG(LogTemp, Warning, TEXT("Upper_Pitch Rotation: %f"), Upper_Pitch);
	
	/*AimDirForward = Rate;
	if (IsLocallyControlled()) {
		
	}
	GetStateDownN()->LookUpAtRate(this, Rate);*/
}

void APlayer_CharacterBase::MoveForward(float Value)
{
	//InputDirForward = Value;
	if (IsMove) {
		InputDirForward = Value;

		if ((Controller != NULL) && (Value != 0.0f)) {
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
			DirMoveForwerd = Direction;
			Direction.Z = 0.0f;
			Direction.Normalize();
			MoveDir += Direction * FMath::Clamp(Value, -1.0f, 1.0f);
			//UE_LOG(LogTemp, Warning, TEXT("InputDirForward: %f"), InputDirForward);
		}
	}
}

void APlayer_CharacterBase::MoveRight(float Value)
{
	//InputDirRight = Value;
	if (IsMove) {
		InputDirRight = Value;

		if ((Controller != NULL) && (Value != 0.0f)) {
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
			Direction.Z = 0.0f;
			Direction.Normalize();
			MoveDir += Direction * FMath::Clamp(Value, -1.0f, 1.0f);
		}
	}
}

void APlayer_CharacterBase::PlayerJump()
{
	bPressedJump = true;
	JumpKeyHoldTime = 0.0f;
}

void APlayer_CharacterBase::PlayerCrouch()
{
	StateDownN->HandleInput(this);
}

void APlayer_CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	StateDownN->StateUpdate(this);
	StateUpperN->StateUpdate(this);

	//Move(DeltaTime);

	SpringArm->SetRelativeLocation(FVector(HeadCameraLoc.X, HeadCameraLoc.Y, HeadCameraLoc.Z));
	//UE_LOG(LogTemp, Warning, TEXT("APlayer_CharacterBase::Tick"));
}

void APlayer_CharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayer_CharacterBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayer_CharacterBase::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APlayer_CharacterBase::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayer_CharacterBase::LookUpAtRate);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayer_CharacterBase::PlayerJump);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &APlayer_CharacterBase::PlayerCrouch);

}

void APlayer_CharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void APlayer_CharacterBase::SetStateUpperN(UPlayerUpper_StateBase* state)
{
	StateUpperN = state;
}

void APlayer_CharacterBase::SetStateDownN(UPlayerDown_StateBase* state)
{
	StateDownN = state;
}

void APlayer_CharacterBase::UpperPress(UPlayerUpper_StateBase* state)
{
	UPlayerUpper_StateBase* UpperState = nullptr;
	if (state == nullptr) {
		UpperState = StateUpperN->HandleInput(this);
		if (UpperState == nullptr) {
			return;
		}
	}
	else { UpperState = state; }
	StateUpperN->StateEnd(this);
	StateUpperBClass = StateUpperN->GetState();
	if (UpperState != nullptr) {
		StateUpperN->DestroyComponent();
		StateUpperN = UpperState;
		StateUpperNClass = StateUpperN->GetState();
		StateUpperN->StateStart(this);
	}
}

void APlayer_CharacterBase::DownPress(UPlayerDown_StateBase* state)
{
	StateDownN->StateEnd(this);
	StateDownBClass = StateDownN->GetState();
	UPlayerDown_StateBase* DownState = nullptr;
	if (state == nullptr) {
		DownState = StateDownN->HandleInput(this);
	}
	else { DownState = state; }
	if (DownState != nullptr) {
		StateDownN->DestroyComponent();
		StateDownN = DownState;
		StateDownNClass = StateDownN->GetState();
		StateDownN->StateStart(this);
	}
}

void APlayer_CharacterBase::Move(float DeltaSeconds)
{
	if (IsMove) {
		if (MoveDir.IsZero()) {
			return;
		}
		//UE_LOG(LogTemp, Warning, TEXT("PlayerSpeed: %f"), PlayerSpeed);
		MoveDir.Normalize();

		//float InputDir = 0.0f;
		if (FMath::Abs(InputDirForward) > FMath::Abs(InputDirRight)) {
			InputDir = FMath::Abs(InputDirForward);
		}
		else { InputDir = FMath::Abs(InputDirRight); }
		//UE_LOG(LogTemp, Warning, TEXT("Input: %f"), FMath::GetMappedRangeValueClamped(FVector2D(0.0f, 1.0f), FVector2D(0.0f, PlayerSpeed), InputDir));
		AddMovementInput(MoveDir, FMath::GetMappedRangeValueClamped(FVector2D(0.0f, 1.0f), FVector2D(0.0f, PlayerSpeed), InputDir) * 0.008f);
		//MoveDir.Set(0.0f, 0.0f, 0.0f);
	}
}

void APlayer_CharacterBase::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(APlayer_CharacterBase, Upper_Pitch, COND_SkipOwner);
	DOREPLIFETIME_CONDITION(APlayer_CharacterBase, Upper_Yaw, COND_SkipOwner);
	DOREPLIFETIME_CONDITION(APlayer_CharacterBase, Upper_Yaw2, COND_SkipOwner);

	//DOREPLIFETIME_CONDITION(APlayer_CharacterBase, StateDownN, COND_SkipOwner);
	//DOREPLIFETIME_CONDITION(APlayer_CharacterBase, StateUpperN, COND_SkipOwner);

	//DOREPLIFETIME(APlayer_CharacterBase, StateDownN);
	//DOREPLIFETIME(APlayer_CharacterBase, StateUpperN);

	/*DOREPLIFETIME_CONDITION(APlayer_CharacterBase, InputDirForward, COND_SkipOwner);
	DOREPLIFETIME_CONDITION(APlayer_CharacterBase, InputDirRight, COND_SkipOwner);*/

}