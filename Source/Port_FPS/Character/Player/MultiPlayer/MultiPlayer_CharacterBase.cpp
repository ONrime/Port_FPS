// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiPlayer_CharacterBase.h"
#include "Port_FPS/Character/Player/PlayerState/PlayerStateBase.h"
#include "Port_FPS/Character/Player/PlayerState/Aim_PlayerUpper_StateBase.h"
#include "Port_FPS/Character/Player/PlayerState/Standing_PlayerDown_StateBase.h"
#include "Port_FPS/Character/Player/PlayerState/MultiPlayer_State/Prone_M_PlayerDown_StateBase.h"
#include "Net/UnrealNetwork.h"

AMultiPlayer_CharacterBase::AMultiPlayer_CharacterBase()
{
	bReplicates = true;
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
	//GetMesh()->bOnlyOwnerSee = true;

}

void AMultiPlayer_CharacterBase::BeginPlay()
{
	Super::BeginPlay();
	BodyMesh->SetOwnerNoSee(true);
	BodyMesh->SetCastShadow(true);
	BodyMesh->bCastHiddenShadow = true;
	GetMesh()->HideBoneByName(FName("spine_03"), PBO_None);
	GetMesh()->SetOnlyOwnerSee(true);
	GetMesh()->SetCastShadow(false);
	//SetStateDownN(NewObject<UProne_M_PlayerDown_StateBase>(this, UProne_M_PlayerDown_StateBase::StaticClass()));
	//GetStateDownN()->StateStart(this);
}

void AMultiPlayer_CharacterBase::TurnAtRate(float Rate)
{
	//Super::TurnAtRate(Rate);
	AimDirRight = Rate;
	GetStateDownN()->TurnAtRate(this, Rate);
}

void AMultiPlayer_CharacterBase::LookUpAtRate(float Rate)
{
	//Super::LookUpAtRate(Rate);
	AimDirForward = Rate;
	GetStateDownN()->LookUpAtRate(this, Rate);
}

void AMultiPlayer_CharacterBase::PlayerJump()
{
	Super::PlayerJump();
}

void AMultiPlayer_CharacterBase::MoveForward(float Value)
{
	Super::MoveForward(Value);
}

void AMultiPlayer_CharacterBase::MoveRight(float Value)
{
	Super::MoveRight(Value);
}


bool AMultiPlayer_CharacterBase::Server_Update_PitchAndYaw_Validate(float Pitch, float Yawm, float Yaw2)
{
	return true;
}

void AMultiPlayer_CharacterBase::Server_Update_PitchAndYaw_Implementation(float Pitch, float Yawm, float Yaw2)
{
	///UE_LOG(LogTemp, Warning, TEXT("Cla_Update: Pitch %f"), Pitch);
	PitchAndYaw();
	testd++;
	UE_LOG(LogTemp, Warning, TEXT("Cla_Update: %s Upper_Pitch2 %f"), *GetName(), testd);
}

void AMultiPlayer_CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority()) { // 서버
		//UE_LOG(LogTemp, Warning, TEXT("Server_Update: Pitch %f"), Upper_Pitch);
		testd++;
		UE_LOG(LogTemp, Warning, TEXT("Server_Update: %s Upper_Pitch2 %f"),*GetName(), testd);
		PitchAndYaw();
	}
	else {  // 클라이언트
		Server_Update_PitchAndYaw_Implementation(Upper_Pitch, Upper_Yaw, Upper_Yaw2);
		
	}
}

void AMultiPlayer_CharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
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
	Upper_Pitch = FMath::ClampAngle(InterpToAngle.Pitch, -90.0f, 90.0f);
	//Upper_Pitch2= FMath::ClampAngle(InterpToAngle.Pitch, -90.0f, 90.0f);
	
}

void AMultiPlayer_CharacterBase::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	/*DOREPLIFETIME_CONDITION(AMultiPlayer_CharacterBase, Upper_Pitch, COND_SkipOwner);
	DOREPLIFETIME_CONDITION(AMultiPlayer_CharacterBase, Upper_Yaw, COND_SkipOwner);
	DOREPLIFETIME_CONDITION(AMultiPlayer_CharacterBase, Upper_Yaw2, COND_SkipOwner);*/
	/*DOREPLIFETIME(AMultiPlayer_CharacterBase, Upper_Pitch);
	DOREPLIFETIME(AMultiPlayer_CharacterBase, Upper_Yaw);
	DOREPLIFETIME(AMultiPlayer_CharacterBase, Upper_Yaw2);*/

	//DOREPLIFETIME(AMultiPlayer_CharacterBase, Upper_Pitch2)
	DOREPLIFETIME(AMultiPlayer_CharacterBase, testd);

}
