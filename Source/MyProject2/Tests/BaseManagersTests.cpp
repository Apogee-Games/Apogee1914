#include "MyGameInstance.h"
#include "Misc/AutomationTest.h"
#include "People/Managers/PeopleManager.h"

namespace BaseManagersTests
{
	struct FTestSetUp
	{
		UMyGameInstance* GameInstance;

		bool bIsInitialized = false;
		
		void Init()
		{
			if (bIsInitialized)
			{
				GameInstance->Shutdown();
			}

			bIsInitialized = true;
			
			GameInstance = NewObject<UMyGameInstance>(GEngine);
			GameInstance->ProvinceManagerClass = UProvinceManager::StaticClass();
			GameInstance->CountriesManagerClass = UCountriesManager::StaticClass();
			GameInstance->ProvinceActorClass = AProvinceActor::StaticClass();

			GameInstance->InitializeStandalone();
		}

		static FTestSetUp& GetInstance()
		{
			static FTestSetUp Instance;
			Instance.Init();
			return Instance;
		}

		static bool IsPersonValid(UPerson* Person, UPersonDescription* PersonDescription)
		{
			return Person && PersonDescription &&
					Person->GetPersonName().ToString() == PersonDescription->Name.ToString() &&
					Person->GetProfessions() == PersonDescription->Professions;
		}

		static bool IsCountryValid(UCountry* Country, UCountryDescription* CountryDescription)
		{
			return Country && CountryDescription &&
				Country->GetName().ToString() == CountryDescription->Ideologies[0].Name.ToString() &&
				Country->GetTag() == CountryDescription->Tag;
		}

		
		static bool IsProvinceValid(UProvince* Province, UProvinceDescription* ProvinceDescription)
		{
			return Province->GetOwnerCountry()->GetDescription() == ProvinceDescription->Country &&
				Province->GetName().ToString() == ProvinceDescription->Name.ToString() &&
				Province->GetId() == ProvinceDescription->Color;
		}
	};

	IMPLEMENT_SIMPLE_AUTOMATION_TEST(PeopleManagerOnePersonOneCountryOneProffesion, "BaseManagersTests.PeopleManagerOnePersonOneCountryOneProffesion", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

	bool PeopleManagerOnePersonOneCountryOneProffesion::RunTest(const FString& Parameters)
	{
		UMyGameInstance* GameInstance = FTestSetUp::GetInstance().GameInstance;

		
		UCountryDescription* CountryDescription = NewObject<UCountryDescription>();
		
		UPersonDescription* PersonDescription = NewObject<UPersonDescription>();
		PersonDescription->Name = FText::FromString(TEXT("Person1"));
		PersonDescription->Country = CountryDescription;

		UProfessionGroup* ProfessionGroup = NewObject<UProfessionGroup>();
		ProfessionGroup->PeopleDescriptions = { PersonDescription };
				
		UProfessionDescription* ProfessionDescription = NewObject<UProfessionDescription>();

		UCountryPeople* CountryPeople = NewObject<UCountryPeople>();
		CountryPeople->ProfessionGroups = { { ProfessionDescription, ProfessionGroup} };

		UScenario* Scenario = NewObject<UScenario>();
		Scenario->PeopleDescriptions = { { CountryDescription, CountryPeople } };

		
		UPeopleManager* PeopleManager = GameInstance->GetSubsystem<UPeopleManager>();
		PeopleManager->SetScenario(Scenario);

		
		const TMap<UPersonDescription*, UPerson*>& People = PeopleManager->GetPeople();
		if (People.Num() != 1)
		{
			return false;
		}

		UPerson* Person = PeopleManager->GetPerson(PersonDescription);
		
		return FTestSetUp::IsPersonValid(Person, PersonDescription);
	}

	IMPLEMENT_SIMPLE_AUTOMATION_TEST(PeopleManagerManyPersonOneCountryOneProffesion, "BaseManagersTests.PeopleManagerManyPersonOneCountryOneProffesion", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

	bool PeopleManagerManyPersonOneCountryOneProffesion::RunTest(const FString& Parameters)
	{
		UMyGameInstance* GameInstance = FTestSetUp::GetInstance().GameInstance;

		
		UCountryDescription* CountryDescription = NewObject<UCountryDescription>();
		
		UProfessionGroup* ProfessionGroup = NewObject<UProfessionGroup>();

		for (int i = 0; i < 10; ++i)
		{
			UPersonDescription* PersonDescription = NewObject<UPersonDescription>();
			PersonDescription->Name = FText::FromString(TEXT("Person1"));
			PersonDescription->Country = CountryDescription;

			ProfessionGroup->PeopleDescriptions.Add(PersonDescription);
		}
		
				
		UProfessionDescription* ProfessionDescription = NewObject<UProfessionDescription>();

		UCountryPeople* CountryPeople = NewObject<UCountryPeople>();
		CountryPeople->ProfessionGroups = { { ProfessionDescription, ProfessionGroup} };

		UScenario* Scenario = NewObject<UScenario>();
		Scenario->PeopleDescriptions = { { CountryDescription, CountryPeople } };

		
		UPeopleManager* PeopleManager = GameInstance->GetSubsystem<UPeopleManager>();
		PeopleManager->SetScenario(Scenario);

		return PeopleManager->GetPeople().Num() == 10;
	}

	IMPLEMENT_SIMPLE_AUTOMATION_TEST(PeopleManagerManyPersonManyCountryOneProffesion, "BaseManagersTests.PeopleManagerManyPersonManyCountryOneProffesion", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

	bool PeopleManagerManyPersonManyCountryOneProffesion::RunTest(const FString& Parameters)
	{
		UMyGameInstance* GameInstance = FTestSetUp::GetInstance().GameInstance;

		
		UCountryDescription* CountryDescription1 = NewObject<UCountryDescription>();
		UCountryDescription* CountryDescription2 = NewObject<UCountryDescription>();

		UProfessionGroup* ProfessionGroup1 = NewObject<UProfessionGroup>();
		UProfessionGroup* ProfessionGroup2 = NewObject<UProfessionGroup>();

		for (int i = 0; i < 10; ++i)
		{
			UPersonDescription* PersonDescription = NewObject<UPersonDescription>();
			PersonDescription->Name = FText::FromString(TEXT("Person1"));
			PersonDescription->Country = CountryDescription1;

			ProfessionGroup1->PeopleDescriptions.Add(PersonDescription);
		}
		
		for (int i = 0; i < 10; ++i)
		{
			UPersonDescription* PersonDescription = NewObject<UPersonDescription>();
			PersonDescription->Name = FText::FromString(TEXT("Person2"));
			PersonDescription->Country = CountryDescription2;

			ProfessionGroup2->PeopleDescriptions.Add(PersonDescription);
		}
				
		UProfessionDescription* ProfessionDescription = NewObject<UProfessionDescription>();

		UCountryPeople* CountryPeople1 = NewObject<UCountryPeople>();
		CountryPeople1->ProfessionGroups = { { ProfessionDescription, ProfessionGroup1} };

		UCountryPeople* CountryPeople2 = NewObject<UCountryPeople>();
		CountryPeople2->ProfessionGroups = { { ProfessionDescription, ProfessionGroup2} };

		
		UScenario* Scenario = NewObject<UScenario>();
		Scenario->PeopleDescriptions = { { CountryDescription1, CountryPeople1 },  { CountryDescription2, CountryPeople2 } };

		
		UPeopleManager* PeopleManager = GameInstance->GetSubsystem<UPeopleManager>();
		PeopleManager->SetScenario(Scenario);
		
		return PeopleManager->GetPeople().Num() == 20 && 
			PeopleManager->GetPeopleByProfession(ProfessionDescription, CountryDescription1).Num() == 10 &&
			PeopleManager->GetPeopleByProfession(ProfessionDescription, CountryDescription2).Num() == 10;
	}
	
	IMPLEMENT_SIMPLE_AUTOMATION_TEST(PeopleManagerManyPersonOneCountryManyProffesions, "BaseManagersTests.PeopleManagerManyPersonOneCountryManyProffesions", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

	bool PeopleManagerManyPersonOneCountryManyProffesions::RunTest(const FString& Parameters)
	{
		UMyGameInstance* GameInstance = FTestSetUp::GetInstance().GameInstance;

		
		UCountryDescription* CountryDescription = NewObject<UCountryDescription>();

		UCountryPeople* CountryPeople = NewObject<UCountryPeople>();
		
		for (int i = 0; i < 10; ++i)
		{
			UProfessionGroup* ProfessionGroup = NewObject<UProfessionGroup>();

			UPersonDescription* PersonDescription = NewObject<UPersonDescription>();
			PersonDescription->Name = FText::FromString(TEXT("Person1"));
			PersonDescription->Country = CountryDescription;

			ProfessionGroup->PeopleDescriptions.Add(PersonDescription);

			UProfessionDescription* ProfessionDescription = NewObject<UProfessionDescription>();

			CountryPeople->ProfessionGroups.Add ({ ProfessionDescription, ProfessionGroup} );
		}
		
		UScenario* Scenario = NewObject<UScenario>();
		Scenario->PeopleDescriptions = { { CountryDescription, CountryPeople } };

		
		UPeopleManager* PeopleManager = GameInstance->GetSubsystem<UPeopleManager>();
		PeopleManager->SetScenario(Scenario);

		return PeopleManager->GetCountryPeople(CountryDescription).Num() == 10;
	}

	IMPLEMENT_SIMPLE_AUTOMATION_TEST(PeopleManagerManyPersonManyCountryManyProffesions, "BaseManagersTests.PeopleManagerManyPersonManyCountryManyProffesions", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

	bool PeopleManagerManyPersonManyCountryManyProffesions::RunTest(const FString& Parameters)
	{
		UMyGameInstance* GameInstance = FTestSetUp::GetInstance().GameInstance;

		
		UCountryDescription* CountryDescription1 = NewObject<UCountryDescription>();
		UCountryDescription* CountryDescription2 = NewObject<UCountryDescription>();

		UCountryPeople* CountryPeople1 = NewObject<UCountryPeople>();
		UCountryPeople* CountryPeople2 = NewObject<UCountryPeople>();

		for (int i = 0; i < 10; ++i)
		{
			UProfessionDescription* ProfessionDescription = NewObject<UProfessionDescription>();
			UProfessionGroup* ProfessionGroup = NewObject<UProfessionGroup>();

			UPersonDescription* PersonDescription = NewObject<UPersonDescription>();
			PersonDescription->Name = FText::FromString(TEXT("Person1"));
			PersonDescription->Country = CountryDescription1;

			ProfessionGroup->PeopleDescriptions = { PersonDescription };

			CountryPeople1->ProfessionGroups.Add(ProfessionDescription, ProfessionGroup);
		}
		
		for (int i = 0; i < 10; ++i)
		{
			UProfessionDescription* ProfessionDescription = NewObject<UProfessionDescription>();
			UProfessionGroup* ProfessionGroup = NewObject<UProfessionGroup>();

			UPersonDescription* PersonDescription = NewObject<UPersonDescription>();
			PersonDescription->Name = FText::FromString(TEXT("Person2"));
			PersonDescription->Country = CountryDescription2;

			ProfessionGroup->PeopleDescriptions = { PersonDescription };

			CountryPeople2->ProfessionGroups.Add(ProfessionDescription, ProfessionGroup);
		}
				
		UScenario* Scenario = NewObject<UScenario>();
		Scenario->PeopleDescriptions = { { CountryDescription1, CountryPeople1 },  { CountryDescription2, CountryPeople2 } };

		
		UPeopleManager* PeopleManager = GameInstance->GetSubsystem<UPeopleManager>();
		PeopleManager->SetScenario(Scenario);
		
		return PeopleManager->GetPeople().Num() == 20 && 
			PeopleManager->GetCountryPeople(CountryDescription1).Num() == 10 &&
			PeopleManager->GetCountryPeople(CountryDescription2).Num() == 10;
	}

	IMPLEMENT_SIMPLE_AUTOMATION_TEST(CountryManagerOneCountry, "BaseManagersTests.CountryManagerOneCountry", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

	bool CountryManagerOneCountry::RunTest(const FString& Parameters)
	{
		UMyGameInstance* GameInstance = FTestSetUp::GetInstance().GameInstance;

		UIdeologyDescription* IdeologyDescription = NewObject<UIdeologyDescription>();
		
		FCountryIdeologyParameters IdeologyParameters;
		
		IdeologyParameters.Ideology = IdeologyDescription;
		IdeologyParameters.Ruler = nullptr;
		IdeologyParameters.Flag = nullptr;

		UCountryDescription* CountryDescription;
		CountryDescription = NewObject<UCountryDescription>();
		CountryDescription->Tag = TEXT("Country1");
		CountryDescription->Ideologies = { IdeologyParameters };
		CountryDescription->CurrentIdeology = IdeologyDescription;

		UScenario* Scenario = NewObject<UScenario>();
		Scenario->CountriesDescriptions = { CountryDescription };

		UCountriesManager* CountriesManager = GameInstance->GetSubsystem<UCountriesManager>();
		CountriesManager->SetScenario(Scenario);

		UCountry* Country = CountriesManager->GetCountry(CountryDescription);
		
		return CountriesManager->GetCountryMap().Num() == 1 && FTestSetUp::IsCountryValid(Country, CountryDescription);
	}

	IMPLEMENT_SIMPLE_AUTOMATION_TEST(CountryManagerManyCountries, "BaseManagersTests.CountryManagerManyCountries", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

	bool CountryManagerManyCountries::RunTest(const FString& Parameters)
	{
		UMyGameInstance* GameInstance = FTestSetUp::GetInstance().GameInstance;
		UScenario* Scenario = NewObject<UScenario>();
		
		UIdeologyDescription* IdeologyDescription = NewObject<UIdeologyDescription>();
		for (int i = 0; i < 10; ++i)
		{
			FCountryIdeologyParameters IdeologyParameters;
		
			IdeologyParameters.Ideology = IdeologyDescription;
			IdeologyParameters.Ruler = nullptr;
			IdeologyParameters.Flag = nullptr;

			UCountryDescription* CountryDescription;
			CountryDescription = NewObject<UCountryDescription>();
			CountryDescription->Tag = TEXT("Country1");
			CountryDescription->Ideologies = { IdeologyParameters };
			CountryDescription->CurrentIdeology = IdeologyDescription;

			Scenario->CountriesDescriptions.Add(CountryDescription);
		}
		
		UCountriesManager* CountriesManager = GameInstance->GetSubsystem<UCountriesManager>();
		CountriesManager->SetScenario(Scenario);

		return CountriesManager->GetCountryMap().Num() == 10;
	}

	IMPLEMENT_SIMPLE_AUTOMATION_TEST(ProvinceManagerOneProvinceOneCountry, "BaseManagersTests.ProvinceManagerOneProvinceOneCountry", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

	bool ProvinceManagerOneProvinceOneCountry::RunTest(const FString& Parameters)
	{
		UMyGameInstance* GameInstance = FTestSetUp::GetInstance().GameInstance;

		UIdeologyDescription* IdeologyDescription = NewObject<UIdeologyDescription>();
		
		FCountryIdeologyParameters IdeologyParameters;
		
		IdeologyParameters.Ideology = IdeologyDescription;
		IdeologyParameters.Ruler = nullptr;
		IdeologyParameters.Flag = nullptr;

		UCountryDescription* CountryDescription;
		CountryDescription = NewObject<UCountryDescription>();
		CountryDescription->Tag = TEXT("Country1");
		CountryDescription->Ideologies = { IdeologyParameters };
		CountryDescription->CurrentIdeology = IdeologyDescription;

		UScenario* Scenario = NewObject<UScenario>();
		Scenario->CountriesDescriptions = { CountryDescription };

		UCountriesManager* CountriesManager = GameInstance->GetSubsystem<UCountriesManager>();
		CountriesManager->SetScenario(Scenario);

		UProvinceDescription* ProvinceDescription = NewObject<UProvinceDescription>();
		ProvinceDescription->Color = FColor::Red;
		ProvinceDescription->Name = FText::FromString(TEXT("Province"));
		ProvinceDescription->Country = CountryDescription;

		UCountryProvinces* CountryProvinces = NewObject<UCountryProvinces>();
		CountryProvinces->Provinces = { ProvinceDescription };
		
		Scenario->ProvincesDescriptions = { { CountryDescription, CountryProvinces } };

		UProvinceManager* ProvinceManager = GameInstance->GetSubsystem<UProvinceManager>();
		ProvinceManager->SetScenario(Scenario);

		UProvince* Province = ProvinceManager->GetProvince(ProvinceDescription->Color);
		
		return ProvinceManager->GetAllProvinces().Num() == 1 && FTestSetUp::IsProvinceValid(Province, ProvinceDescription);
	}

	IMPLEMENT_SIMPLE_AUTOMATION_TEST(ProvinceManagerManyProvinceOneCountry, "BaseManagersTests.ProvinceManagerManyProvinceOneCountry", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

	bool ProvinceManagerManyProvinceOneCountry::RunTest(const FString& Parameters)
	{
		UMyGameInstance* GameInstance = FTestSetUp::GetInstance().GameInstance;

		UIdeologyDescription* IdeologyDescription = NewObject<UIdeologyDescription>();
		
		FCountryIdeologyParameters IdeologyParameters;
		
		IdeologyParameters.Ideology = IdeologyDescription;
		IdeologyParameters.Ruler = nullptr;
		IdeologyParameters.Flag = nullptr;

		UCountryDescription* CountryDescription;
		CountryDescription = NewObject<UCountryDescription>();
		CountryDescription->Tag = TEXT("Country1");
		CountryDescription->Ideologies = { IdeologyParameters };
		CountryDescription->CurrentIdeology = IdeologyDescription;

		UScenario* Scenario = NewObject<UScenario>();
		Scenario->CountriesDescriptions = { CountryDescription };

		UCountriesManager* CountriesManager = GameInstance->GetSubsystem<UCountriesManager>();
		CountriesManager->SetScenario(Scenario);

		UCountryProvinces* CountryProvinces = NewObject<UCountryProvinces>();
		for (int i = 0; i < 10; ++i)
		{
			UProvinceDescription* ProvinceDescription = NewObject<UProvinceDescription>();
			ProvinceDescription->Color = FColor(i);
			ProvinceDescription->Name = FText::FromString(TEXT("Province"));
			ProvinceDescription->Country = CountryDescription;

			CountryProvinces->Provinces.Add(ProvinceDescription);
		}		
		Scenario->ProvincesDescriptions = { { CountryDescription, CountryProvinces } };

		UProvinceManager* ProvinceManager = GameInstance->GetSubsystem<UProvinceManager>();
		ProvinceManager->SetScenario(Scenario);

		for (const auto& Province: ProvinceManager->GetAllProvinces())
		{
			if (Province->GetOwnerCountry()->GetDescription() != CountryDescription)
			{
				return false;
			}
		}
		
		return ProvinceManager->GetAllProvinces().Num() == 10;
	}

	IMPLEMENT_SIMPLE_AUTOMATION_TEST(ProvinceManagerManyProvinceManyCountries, "BaseManagersTests.ProvinceManagerManyProvinceManyCountries", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

	bool ProvinceManagerManyProvinceManyCountries::RunTest(const FString& Parameters)
	{
		UMyGameInstance* GameInstance = FTestSetUp::GetInstance().GameInstance;

		UIdeologyDescription* IdeologyDescription = NewObject<UIdeologyDescription>();
		
		
		UScenario* Scenario = NewObject<UScenario>();


		UCountryProvinces* CountryProvinces = NewObject<UCountryProvinces>();
		for (int i = 0; i < 10; ++i)
		{
			FCountryIdeologyParameters IdeologyParameters;
		
			IdeologyParameters.Ideology = IdeologyDescription;
			IdeologyParameters.Ruler = nullptr;
			IdeologyParameters.Flag = nullptr;

			UCountryDescription* CountryDescription;
			CountryDescription = NewObject<UCountryDescription>();
			CountryDescription->Tag = TEXT("Country1");
			CountryDescription->Ideologies = { IdeologyParameters };
			CountryDescription->CurrentIdeology = IdeologyDescription;

			UProvinceDescription* ProvinceDescription = NewObject<UProvinceDescription>();
			ProvinceDescription->Color = FColor(i);
			ProvinceDescription->Name = FText::FromString(TEXT("Province"));
			ProvinceDescription->Country = CountryDescription;

			CountryProvinces->Provinces.Add(ProvinceDescription);
			
			Scenario->CountriesDescriptions.Add(CountryDescription);

			Scenario->ProvincesDescriptions.Add({ CountryDescription, CountryProvinces });
		}		

		UCountriesManager* CountriesManager = GameInstance->GetSubsystem<UCountriesManager>();
		CountriesManager->SetScenario(Scenario);

		UProvinceManager* ProvinceManager = GameInstance->GetSubsystem<UProvinceManager>();
		ProvinceManager->SetScenario(Scenario);

		for (const auto& [CountryDescription, ProvinceDescription]: Scenario->ProvincesDescriptions)
		{
			UProvince* Province = ProvinceManager->GetProvince(ProvinceDescription->Provinces[0]->Color);
			if (Province->GetOwnerCountry()->GetDescription() != ProvinceDescription->Provinces[0]->Country)
			{
				return false;
			}
		}
		
		return ProvinceManager->GetAllProvinces().Num() == 10;
	}
}
