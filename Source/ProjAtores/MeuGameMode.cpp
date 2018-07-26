// Fill out your copyright notice in the Description page of Project Settings.

//Includes necessários para utilizar diversos recursos e classes no código
// Indica ao Compilador onde ele via encontrar as funções e classes utilizadas
//E no momento da Linkedicação ele vai colocar o código relativo a estas funções e classes
#include "MeuGameMode.h"
#include "Engine/TargetPoint.h"
#include "Kismet/GameplayStatics.h"
#include "Granada.h"
#include "Engine/World.h"
#include "Engine/Engine.h"


void AMeuGameMode::StartPlay()
{
	Super::StartPlay();
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Estou no Game Mode \n Granadas Lancadas!"));
}


//Game mode é uma classe que contém as regras e configurações do nosso jogo
// Cada level pode ter seu próprio game mode
// Para isso em World Settings você pode s1obrescrever o gamemode padrão pelo seu gamemode
// Caso deseje substituir o gamemode para todos os levels use Edit->Project Settings
void AMeuGameMode::BeginPlay()
{
	Super::BeginPlay();
	//Aqui declara uma variavel de nome LocalGranadas do tipo array dinâmico capaz
	//de armazenar ponteiros(Endereços de memória) do tipo AActor ou subclasses de AActor
	TArray<AActor*> LocalGranadas;
	//A função vai percorrer o mundo em busca de TargetPoints e cada Objeto deste tipo encontrado
	//Irá adicionar no array dinâmico LocalGranadas o endereço de memória de cada Target Point
	//No nosso caso serão coletados 7 endereços e memória e armazenados neste TArray LocalGranadas
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), LocalGranadas);
	//UE_LOG(LogTemp, Warning, TEXT("Num de Target Point Encontrados %d"), LocalGranadas.Num());
	if (LocalGranadas.Num() != 0)
	{
		//FActorSpawnParemets são configurações que você pode criar adicionalmente para quando
		// Criar um ator através da função SpawnActor
		// Contudo na maoria das vezes será apenas necessário os valores padrão
		//Assim criamos uma variável params e iniciamos ela com valores padrão através
		// do resultado da chamda do construtor de FActorSapwnParamets
		FActorSpawnParameters params = FActorSpawnParameters();
		//Vai Iterar(Percorrer o TArray LocalGRanadas e a cada passada pelos índices de 0 a 6
		//pois são 7 elementos o comando for vai colocando dentro da variável It o endereço de memória
		//de cada posição do Array dinâmico LocalGranadas
		// Assim It é um iterador algo como um cursor que vai está apontando para o array
		// Então It contém um endereço de memória e desta forma ele é um PONTEIRO
		//Para encontrar e verificar o conteúdo que It está apontando fazemos (*it).GetActorLocation()
		// PAra simplicar usamos a notação flecha it->GetActorLocation();
		//Podemos ler assim: It vá lá no endereço de memória que você está apontando e me diga
		// a localização deste local...
		int32 i = 0;
		for (auto It : LocalGranadas) {
			GetWorld()->SpawnActor<AGranada>(It->GetActorLocation(), It->GetActorRotation(), params);
			//UE_LOG(LogTemp, Warning, TEXT("O que esta contido: %p em LocalGranda no Indice %d"), It, i++);
			//GEngine->AddOnScreenDebugMessage(-1, -1, FColor::Red, TEXT("Ator Gerado"));
			//UE_LOG(LogTemp, Warning, TEXT("Transform = %s"), *It->GetActorLocation().ToString())

		}

	
	}
}





