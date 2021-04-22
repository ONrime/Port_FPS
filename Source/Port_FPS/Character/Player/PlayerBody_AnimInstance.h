// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerBody_AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PORT_FPS_API UPlayerBody_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPlayerBody_AnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Base, Meta = (AllowPrivateAccess = true))
	float PlayerSpeed = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Base, Meta = (AllowPrivateAccess = true))
	bool IsAir = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Base, Meta = (AllowPrivateAccess = true))
	float DirForward = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Base, Meta = (AllowPrivateAccess = true))
	float DirRight = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Base, Meta = (AllowPrivateAccess = true))
	float Upper_Pitch = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Base, Meta = (AllowPrivateAccess = true))
	float Upper_Yaw = 0.0f;
	
};
