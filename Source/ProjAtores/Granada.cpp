// Fill out your copyright notice in the Description page of Project Settings.

#include "Granada.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/EngineTypes.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/AudioComponent.h"
#include "TimerManager.h"
#include "Sound/SoundCue.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/StaticMeshActor.h"
#include "Public/EngineUtils.h"
#include "UObject/UObjectIterator.h"
#include "Components/SkeletalMeshComponent.h"




// Sets default values
AGranada::AGranada()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ColisorDoAtor = CreateDefaultSubobject<USphereComponent>(FName("Colisor"));
	ColisorDoAtor->SetSphereRadius(12.f);
	ColisorDoAtor->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RootComponent = ColisorDoAtor;

	MalhaDoAtor = CreateDefaultSubobject<UStaticMeshComponent>(FName("Malha"));
	MalhaDoAtor->SetRelativeLocation(FVector(3.2f, 0.f, 0.f));
	MalhaDoAtor->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	MalhaDoAtor->SetupAttachment(RootComponent);

	SomDaExplosao = CreateDefaultSubobject<UAudioComponent>(FName("Som da Explosao"));
	SomDaExplosao->bAutoActivate = false;
	SomDaExplosao->bAutoDestroy = true;
	SomDaExplosao->SetupAttachment(MalhaDoAtor);

	Explosao = CreateDefaultSubobject<UParticleSystemComponent>(FName("Particula Explosao"));
	Explosao->bAutoActivate = false;
	Explosao->bAutoDestroy = true;
	Explosao->SetupAttachment(MalhaDoAtor);
	
	ConstructorHelpers::FObjectFinder<USoundCue>SomGranada(TEXT("SoundCue'/Game/StarterContent/Audio/Explosion_Cue.Explosion_Cue'"));

	ConstructorHelpers::FObjectFinder<UStaticMesh>Granada(TEXT("StaticMesh'/Game/FBX/granede.granede'"));

	ConstructorHelpers::FObjectFinder<UParticleSystem>ParticulaExplosao(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));

	if(Granada.Succeeded() && SomGranada.Succeeded() && ParticulaExplosao.Succeeded()){
		MalhaDoAtor->SetStaticMesh(Granada.Object);
		SomDaExplosao->SetSound(SomGranada.Object);
		Explosao->SetTemplate(ParticulaExplosao.Object);
	}


}

void AGranada::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	//Ser� colocado na tela durante 5 segunds (5.f) em cor vermelha o texto indicado
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Granada Destruida!");
	//Aqui estamos excluindo o manipulador(handle) de nome Temporatizador
	//A partir daqui ele ser� inv�lido!
	GetWorldTimerManager().ClearTimer(Temporizador);
}

// Called when the game starts or when spawned
void AGranada::BeginPlay()
{
	Super::BeginPlay();
	TempoDevagar(0.1);
	MalhaDoAtor->SetSimulatePhysics(true);
	MalhaDoAtor->SetEnableGravity(true);
	GetWorldTimerManager().SetTimer(Temporizador, this, &AGranada::ExplodirGranada, 5.f, false);
		
	
}

void AGranada::TempoDevagar(float DilatacaoDoTempo)
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), DilatacaoDoTempo);
	GetWorldTimerManager().SetTimer(TimerDoTempo, this, &AGranada::RestaurarTempo, (3.f * DilatacaoDoTempo), false);
}

void AGranada::RestaurarTempo()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);
	GetWorldTimerManager().ClearTimer(TimerDoTempo);

}

void AGranada::ImpulsoRadial(float Raio, float Forca)
{
	for (TActorIterator<AStaticMeshActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		
			UStaticMeshComponent* RaizDoStaticMesh;
			RaizDoStaticMesh = Cast<UStaticMeshComponent>(ActorItr->GetRootComponent());
			if (RaizDoStaticMesh)
			{
				if (RaizDoStaticMesh->Mobility == EComponentMobility::Movable)
				{
					UE_LOG(LogTemp, Warning, TEXT("Nome: %s %X"), *ActorItr->GetName(), *ActorItr);
					RaizDoStaticMesh->SetSimulatePhysics(true);
					RaizDoStaticMesh->AddRadialImpulse(GetActorLocation(), Raio, Forca, ERadialImpulseFalloff::RIF_Linear, true);
				}
			}
	}

	for(TObjectIterator<USkeletalMeshComponent> It; It; ++It)
	{ 
		if(It->GetWorld() == GetWorld())
		{ 
			UE_LOG(LogTemp, Warning, TEXT("Nome: %s End: %X \n"), *It->GetName(), *It);
			It->SetSimulatePhysics(true);
			It->AddRadialImpulse(GetActorLocation(), Raio, Forca, ERadialImpulseFalloff::RIF_Linear, true);
		}
	}
}

void AGranada::ExplodirGranada()
{
	SetLifeSpan(5.5f);
	SomDaExplosao->Play();
	TempoDevagar(0.05);
	Explosao->ActivateSystem();
	MalhaDoAtor->SetVisibility(false);
	ImpulsoRadial(5000.f, 1000.f);
}

// Called every frame
void AGranada::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



