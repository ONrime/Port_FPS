// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_CharacterBase.h"

APlayer_CharacterBase::APlayer_CharacterBase()
{
	//GetCapsuleComponent()->SetCollisionProfileName("");
	
	//GetMesh()->SetCollisionProfileName("");
	/*static ConstructorHelpers::FObjectFinder<USkeletalMesh>FULLBODY_SKELETALMESH(TEXT("SkeletalMesh'/Game/PlayerFile/Mesh/SC_Cyborg_Soldier_V3.SC_Cyborg_Soldier_V3'"));
	if (FULLBODY_SKELETALMESH.Succeeded()) { GetMesh()->SetSkeletalMesh(FULLBODY_SKELETALMESH.Object); }
	static ConstructorHelpers::FClassFinder<UAnimInstance>FULLBODY_ANIMBP(TEXT("AnimBlueprint'/Game/PlayerFile/Animation/Body/AnimBP_Player_Down.AnimBP_Player_Down_C'"));
	if (FULLBODY_ANIMBP.Succeeded()) { GetMesh()->SetAnimInstanceClass(FULLBODY_ANIMBP.Class); }*/

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 65.0f));
	SpringArm->bDoCollisionTest = true;
	SpringArm->TargetArmLength = 0.0f;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritRoll = false;
	SpringArm->bInheritYaw = false;

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

	GetCharacterMovement()->bOrientRotationToMovement = false; // �̵����⿡ ���缭 ȸ���� �������ش�.(ȸ���� ���� �ٲٱ� ������ false)	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 0.0f, 0.0f); // ȸ�� �ӵ� 0.0���� �ʱ�ȭ (�� ����?)
	GetCharacterMovement()->JumpZVelocity = 500.0f;
	GetCharacterMovement()->AirControl = 0.2f;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;  // ��Ʈ�ѷ� �������� ĳ���� ȸ��(�����Ʈ ����)
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 1000.0f, 0.0f); // �������� �ӵ� ����
	GetCharacterMovement()->MovementMode = EMovementMode::MOVE_Walking;
}

void APlayer_CharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void APlayer_CharacterBase::TurnAtRate(float Rate)
{
	AimDirRight = Rate;
	float Deltatime = GetWorld()->GetDeltaSeconds();
	FRotator InterpToAngle = FMath::RInterpTo(FRotator(0.0f, Upper_Yaw, 0.0f), ((GetControlRotation() - GetActorRotation()).GetNormalized()), Deltatime, 500.0f);
	Upper_Yaw = FMath::ClampAngle(InterpToAngle.Yaw, -90.0f, 90.0f);
	Upper_Yaw2 = InterpToAngle.Yaw;
	//UE_LOG(LogTemp, Warning, TEXT("Upper_Yaw Rotation: %f"), YawUpper_Yaw);

}

void APlayer_CharacterBase::LookUpAtRate(float Rate)
{
	AimDirForward = Rate;
	float Deltatime = GetWorld()->GetDeltaSeconds();
	FRotator InterpToAngle = FMath::RInterpTo(FRotator(Upper_Pitch, 0.0f, 0.0f), ((GetControlRotation() - GetActorRotation()).GetNormalized()), Deltatime, 500.0f);
	FMath::ClampAngle(InterpToAngle.Pitch, -90.0f, 90.0f);
	Upper_Pitch = FMath::ClampAngle(InterpToAngle.Pitch, -90.0f, 90.0f);
	//UE_LOG(LogTemp, Warning, TEXT("Upper_Pitch Rotation: %f"), Upper_Pitch);

	//float PitchRate = Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds();
	//AddControllerPitchInput(PitchRate);
}

void APlayer_CharacterBase::PlayerJump()
{
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


void APlayer_CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move(DeltaTime);
}

void APlayer_CharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayer_CharacterBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayer_CharacterBase::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APlayer_CharacterBase::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayer_CharacterBase::LookUpAtRate);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayer_CharacterBase::PlayerJump);

}

void APlayer_CharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void APlayer_CharacterBase::Move(float DeltaSeconds)
{
	if (IsMove) {
		if (MoveDir.IsZero()) {
			return;
		}
		//UE_LOG(LogTemp, Warning, TEXT("PlayerSpeed: %f"), PlayerSpeed);
		MoveDir.Normalize();

		float InputDir = 0.0f;
		if (FMath::Abs(InputDirForward) > FMath::Abs(InputDirRight)) {
			InputDir = FMath::Abs(InputDirForward);
		}
		else { InputDir = FMath::Abs(InputDirRight); }
		//UE_LOG(LogTemp, Warning, TEXT("Input: %f"), FMath::GetMappedRangeValueClamped(FVector2D(0.0f, 1.0f), FVector2D(0.0f, PlayerSpeed), InputDir));
		AddMovementInput(MoveDir, FMath::GetMappedRangeValueClamped(FVector2D(0.0f, 1.0f), FVector2D(0.0f, PlayerSpeed), InputDir) * DeltaSeconds);
		//MoveDir.Set(0.0f, 0.0f, 0.0f);
	}
}
