#include "MyGameInstance.h"
#include "Military/Managers/UnitsFactory.h"
#include "Misc/AutomationTest.h"
#include "People/Managers/PeopleManager.h"

namespace FactoryTests 
{
		
	struct FTestSetUp
	{
		UMyGameInstance* GameInstance;

		UIdeologyDescription* IdeologyDescription;

		UPersonDescription* PersonDescription1;
		UPersonDescription* PersonDescription2;


		UProfessionDescription* ProfessionDescription;

		
		UMilitaryBranchDescription* MilitaryBranch;

		
		UUnitDescription* UnitDescription1;
		UUnitDescription* UnitDescription2;


		UProfessionGroup* ProfessionGroup1;
		UProfessionGroup* ProfessionGroup2;

		UCountryPeople* CountryPeople1;
		UCountryPeople* CountryPeople2;

		FCountryIdeologyParameters IdeologyParameters1;
		FCountryIdeologyParameters IdeologyParameters2;

		UCountryProvinces* CountryProvinces1;
		UCountryProvinces* CountryProvinces2;

		UCountryDescription* CountryDescription1;
		UCountryDescription* CountryDescription2;

		UCountry* Country1;
		UCountry* Country2;


		UProvinceDescription* ProvinceDescription1;
		UProvinceDescription* ProvinceDescription2;
		UProvinceDescription* ProvinceDescription3;
		
		UProvince* Province1;
		UProvince* Province2;
		UProvince* Province3;


		UWar* War;
		
		UScenario* Scenario;

		bool bIsInitialized = false;
		
		void Init()
		{
			if (bIsInitialized)
			{
				GameInstance->Shutdown();
			}

			bIsInitialized = true;
			
			// GameInstance Initialization
			GameInstance = NewObject<UMyGameInstance>(GEngine);
			GameInstance->ProvinceManagerClass = UProvinceManager::StaticClass();
			GameInstance->CountriesManagerClass = UCountriesManager::StaticClass();
			GameInstance->ProvinceActorClass = AProvinceActor::StaticClass();

			GameInstance->InitializeStandalone();
			
			// Scenario

			IdeologyDescription = NewObject<UIdeologyDescription>();
			IdeologyDescription->Name = FText::FromString(TEXT("None"));
			
			PersonDescription1 = NewObject<UPersonDescription>();
			PersonDescription1->Name = FText::FromString(TEXT("Person1"));
			PersonDescription1->Country = CountryDescription2;

			PersonDescription2 = NewObject<UPersonDescription>();
			PersonDescription2->Name = FText::FromString(TEXT("Person2"));
			PersonDescription2->Country = CountryDescription2;
			
			
			IdeologyParameters1.Ideology = IdeologyDescription;
			IdeologyParameters1.Ruler = PersonDescription1;
			IdeologyParameters1.Flag = nullptr;
			
			CountryDescription1 = NewObject<UCountryDescription>();
			CountryDescription1->Tag = TEXT("Country1");
			CountryDescription1->Ideologies = { IdeologyParameters1 };
			CountryDescription1->CurrentIdeology = IdeologyDescription;

			IdeologyParameters2.Ideology = IdeologyDescription;
			IdeologyParameters2.Ruler = PersonDescription1;
			IdeologyParameters2.Flag = nullptr;

			CountryDescription2 = NewObject<UCountryDescription>();
			CountryDescription2->Tag = TEXT("Country2");
			CountryDescription2->Ideologies = { IdeologyParameters2 };
			CountryDescription2->CurrentIdeology = IdeologyDescription;

			
			ProvinceDescription1 = NewObject<UProvinceDescription>();
			ProvinceDescription1->Country = CountryDescription1;
			ProvinceDescription1->Name = FText::FromString(TEXT("Province1"));
			ProvinceDescription1->Color = FColor::Red;

			ProvinceDescription2 = NewObject<UProvinceDescription>();
			ProvinceDescription2->Country = CountryDescription1;
			ProvinceDescription2->Name = FText::FromString(TEXT("Province2"));
			ProvinceDescription2->Color = FColor::Blue;

			ProvinceDescription3 = NewObject<UProvinceDescription>();
			ProvinceDescription3->Country = CountryDescription2;
			ProvinceDescription3->Name = FText::FromString(TEXT("Province3"));
			ProvinceDescription3->Color = FColor::Green;

			CountryProvinces1 = NewObject<UCountryProvinces>();
			CountryProvinces1->Provinces = { ProvinceDescription1, ProvinceDescription2 };

			CountryProvinces2 = NewObject<UCountryProvinces>();
			CountryProvinces2->Provinces = { ProvinceDescription3 };

			
			ProfessionDescription = NewObject<UProfessionDescription>();
			
			ProfessionGroup1 = NewObject<UProfessionGroup>();
			ProfessionGroup1->PeopleDescriptions = { PersonDescription1 };
			
			CountryPeople1 = NewObject<UCountryPeople>();
			CountryPeople1->ProfessionGroups = { { ProfessionDescription, ProfessionGroup1 } }; 

			ProfessionGroup2 = NewObject<UProfessionGroup>();
			ProfessionGroup2->PeopleDescriptions = { PersonDescription2 };

			CountryPeople2 = NewObject<UCountryPeople>();
			CountryPeople2->ProfessionGroups = { { ProfessionDescription, ProfessionGroup2 } }; 
			
			Scenario = NewObject<UScenario>();
			Scenario->CountriesDescriptions = { CountryDescription1, CountryDescription2 };
			Scenario->ProvincesDescriptions = { { CountryDescription1, CountryProvinces1 }, {CountryDescription2, CountryProvinces2 } };
			Scenario->PeopleDescriptions = { { CountryDescription1, CountryPeople1 }, { CountryDescription2, CountryPeople2 } };
			
			// Managers

			UPeopleManager* PeopleManager = GameInstance->GetSubsystem<UPeopleManager>();
			PeopleManager->SetScenario(Scenario);
			
			UCountriesManager* CountriesManager = GameInstance->GetSubsystem<UCountriesManager>();
			CountriesManager->SetScenario(Scenario);

			UProvinceManager* ProvinceManager = GameInstance->GetSubsystem<UProvinceManager>();
			ProvinceManager->SetScenario(Scenario);
			
			// Objects 

			Country1 = CountriesManager->GetCountry(CountryDescription1);
			Country2 = CountriesManager->GetCountry(CountryDescription2);
			
			Province1 = ProvinceManager->GetProvince(ProvinceDescription1->Color);
			Province1->InitProvinceActor({0, 0, 0}, {0, 0}, {0, 0});

			Province2 = ProvinceManager->GetProvince(ProvinceDescription2->Color);
			Province2->InitProvinceActor({0, 0, 0}, {0, 0}, {0, 0});

			Province3 = ProvinceManager->GetProvince(ProvinceDescription3->Color);
			Province3->InitProvinceActor({0, 0, 0}, {0, 0}, {0, 0});
		
		    MilitaryBranch = NewObject<UMilitaryBranchDescription>();
			MilitaryBranch->UnitClass = UDivision::StaticClass();
		    

			UnitDescription1 = NewObject<UUnitDescription>();
			
		    UnitDescription1->UnitName = "Unit1";
		    UnitDescription1->Attack = 0.0f;
		    UnitDescription1->Defence = 0.0f;
		    UnitDescription1->CanTransport = false;
		    UnitDescription1->ManpowerRequirements = 10000;
		    UnitDescription1->MilitaryBranch = MilitaryBranch;

			UnitDescription2 = NewObject<UUnitDescription>();
			
			UnitDescription2->UnitName = "Unit2";
			UnitDescription2->Attack = 0.0f;
			UnitDescription2->Defence = 0.0f;
			UnitDescription2->CanTransport = false;
			UnitDescription2->ManpowerRequirements = 10000;
			UnitDescription2->MilitaryBranch = MilitaryBranch;

			War = NewObject<UWar>();
			War->Init(Country1, Country2);
		}

		static bool IsUnitCorrect(UUnit* Unit, UUnitDescription* UnitDescription, UProvince* Province)
		{
			return Unit->GetManpower() == UnitDescription->ManpowerRequirements &&
				   Unit->GetPosition() == Province &&
				   Unit->GetMilitaryBranch() == UnitDescription->MilitaryBranch &&
				   Unit->CanTransportUnits() == UnitDescription->CanTransport;
		}

		static FTestSetUp& GetInstance()
		{
			static FTestSetUp Instance;
			return Instance;
		} 
	};

	IMPLEMENT_SIMPLE_AUTOMATION_TEST(OneUnit, "UnitsFactory.OneUnit", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::PerfFilter)

	bool OneUnit::RunTest(const FString& Parameters)
	{
		FTestSetUp& TestSetUp = FTestSetUp::GetInstance();
		TestSetUp.Init();
		
		UUnitsFactory* Factory = TestSetUp.GameInstance->GetSubsystem<UUnitsFactory>();

		UUnit* Unit = Factory->CreateUnit(TestSetUp.UnitDescription1, TestSetUp.Province1);
    		
		return FTestSetUp::IsUnitCorrect(Unit, TestSetUp.UnitDescription1, TestSetUp.Province1) && Factory->GetUnits().Num() == 1;
	}


	IMPLEMENT_SIMPLE_AUTOMATION_TEST(MultipleUnitsInOneProvince, "UnitsFactory.MultipleUnitsInOneProvince", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::PerfFilter)

	bool MultipleUnitsInOneProvince::RunTest(const FString& Parameters)
	{
		FTestSetUp& TestSetUp = FTestSetUp::GetInstance();
		TestSetUp.Init();
		
		UUnitsFactory* Factory = TestSetUp.GameInstance->GetSubsystem<UUnitsFactory>();

		bool IsCorrect = true;
		
		for (int i = 0; i < 10; ++i)
		{
			UUnit* Unit = Factory->CreateUnit(TestSetUp.UnitDescription1, TestSetUp.Province1);
	    
			IsCorrect = IsCorrect && FTestSetUp::IsUnitCorrect(Unit, TestSetUp.UnitDescription1, TestSetUp.Province1);
		}
		
		return IsCorrect && Factory->GetUnits().Num() == 10;
	}


	IMPLEMENT_SIMPLE_AUTOMATION_TEST(TwoUnitsInDifferentProvinces, "UnitsFactory.TwoUnitsInDifferentProvinces", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::PerfFilter)

	bool TwoUnitsInDifferentProvinces::RunTest(const FString& Parameters)
	{
		FTestSetUp& TestSetUp = FTestSetUp::GetInstance();
		TestSetUp.Init();
		
		UUnitsFactory* Factory = TestSetUp.GameInstance->GetSubsystem<UUnitsFactory>();

		UUnit* Unit1 = Factory->CreateUnit(TestSetUp.UnitDescription1, TestSetUp.Province1);
		UUnit* Unit2 = Factory->CreateUnit(TestSetUp.UnitDescription1, TestSetUp.Province2);
		
		return Unit1->GetUnitDescription() == Unit1->GetUnitDescription() &&
			   Unit1->GetPosition() != Unit2->GetPosition() &&
			   Factory->GetUnits().Num() == 2;
	}


	IMPLEMENT_SIMPLE_AUTOMATION_TEST(TwoDifferentUnitsInOneProvinces, "UnitsFactory.TwoDifferentUnitsInOneProvinces", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::PerfFilter)

	bool TwoDifferentUnitsInOneProvinces::RunTest(const FString& Parameters)
	{
		FTestSetUp& TestSetUp = FTestSetUp::GetInstance();
		TestSetUp.Init();
		
		UUnitsFactory* Factory = TestSetUp.GameInstance->GetSubsystem<UUnitsFactory>();

		UUnit* Unit1 = Factory->CreateUnit(TestSetUp.UnitDescription1, TestSetUp.Province1);
		UUnit* Unit2 = Factory->CreateUnit(TestSetUp.UnitDescription2, TestSetUp.Province1);
		
		return Unit1->GetUnitDescription() != Unit2->GetUnitDescription() &&
			   Unit1->GetPosition() == Unit2->GetPosition() &&
			   Factory->GetUnits().Num() == 2;
	}


	IMPLEMENT_SIMPLE_AUTOMATION_TEST(TwoDifferentUnitsInDifferentProvinces, "UnitsFactory.TwoDifferentUnitsInDifferentProvinces", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::PerfFilter)

	bool TwoDifferentUnitsInDifferentProvinces::RunTest(const FString& Parameters)
	{
		FTestSetUp& TestSetUp = FTestSetUp::GetInstance();
		TestSetUp.Init();
		
		UUnitsFactory* Factory = TestSetUp.GameInstance->GetSubsystem<UUnitsFactory>();

		UUnit* Unit1 = Factory->CreateUnit(TestSetUp.UnitDescription1, TestSetUp.Province1);
		UUnit* Unit2 = Factory->CreateUnit(TestSetUp.UnitDescription2, TestSetUp.Province2);
		
		return Unit1->GetUnitDescription() != Unit2->GetUnitDescription() &&
			   Unit1->GetPosition() != Unit2->GetPosition() &&
			   Factory->GetUnits().Num() == 2;
	}

	IMPLEMENT_SIMPLE_AUTOMATION_TEST(OneUnitInAnotherCountyProvince, "UnitsFactory.OneUnitInAnotherCountyProvince", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::PerfFilter)

	bool OneUnitInAnotherCountyProvince::RunTest(const FString& Parameters)
	{
		FTestSetUp& TestSetUp = FTestSetUp::GetInstance();
		TestSetUp.Init();
		
		UUnitsFactory* Factory = TestSetUp.GameInstance->GetSubsystem<UUnitsFactory>();

		Factory->CreateUnit(TestSetUp.UnitDescription1, TestSetUp.Province1, TestSetUp.CountryDescription2);
		
		return TestSetUp.Province1->GetCountryController() == TestSetUp.Country2;
	}

	IMPLEMENT_SIMPLE_AUTOMATION_TEST(OneUnitsCollection, "UnitsFactory.OneUnitsCollection", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::PerfFilter)

	bool OneUnitsCollection::RunTest(const FString& Parameters)
	{
		FTestSetUp& TestSetUp = FTestSetUp::GetInstance();
		TestSetUp.Init();
		
		UUnitsFactory* Factory = TestSetUp.GameInstance->GetSubsystem<UUnitsFactory>();

		UUnitsCollection* UnitsCollection = Factory->CreateUnitCollection(TestSetUp.MilitaryBranch, TestSetUp.Country1);
		
		return UnitsCollection->GetMilitaryBranch() == TestSetUp.MilitaryBranch && UnitsCollection->GetCountryOwner() == TestSetUp.Country1;
	}

	IMPLEMENT_SIMPLE_AUTOMATION_TEST(OneUnitsCollectionGroup, "UnitsFactory.OneUnitsCollectionGroup", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::PerfFilter)

	bool OneUnitsCollectionGroup::RunTest(const FString& Parameters)
	{
		FTestSetUp& TestSetUp = FTestSetUp::GetInstance();
		TestSetUp.Init();
		
		UUnitsFactory* Factory = TestSetUp.GameInstance->GetSubsystem<UUnitsFactory>();

		UUnitsCollectionGroup* UnitsCollectionGroup = Factory->CreateUnitCollectionGroup(TestSetUp.MilitaryBranch, TestSetUp.Country1);
		
		return UnitsCollectionGroup->GetMilitaryBranch() == TestSetUp.MilitaryBranch && UnitsCollectionGroup->GetCountryOwner() == TestSetUp.Country1;
	}


	IMPLEMENT_SIMPLE_AUTOMATION_TEST(OneUnitsCollectionWithUnits, "UnitsFactory.OneUnitsCollectionWithUnits", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::PerfFilter)

	bool OneUnitsCollectionWithUnits::RunTest(const FString& Parameters)
	{
		FTestSetUp& TestSetUp = FTestSetUp::GetInstance();
		TestSetUp.Init();
		
		UUnitsFactory* Factory = TestSetUp.GameInstance->GetSubsystem<UUnitsFactory>();
		
		UUnit* Unit = Factory->CreateUnit(TestSetUp.UnitDescription1, TestSetUp.Province1);
		UUnitsCollection* UnitsCollection = Factory->CreateUnitCollection(TestSetUp.MilitaryBranch, TestSetUp.Country1, { Unit });
		
		return UnitsCollection->GetMilitaryBranch() == TestSetUp.MilitaryBranch &&
			UnitsCollection->GetCountryOwner() == TestSetUp.Country1 &&
			UnitsCollection->GetAll().Num() == 1 &&
			UnitsCollection->GetAll().Contains(Unit);
	}


	IMPLEMENT_SIMPLE_AUTOMATION_TEST(OneUnitsCollectionGroupWithUnitsCollections, "UnitsFactory.OneUnitsCollectionGroupWithUnitsCollections", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::PerfFilter)

	bool OneUnitsCollectionGroupWithUnitsCollections::RunTest(const FString& Parameters)
	{
		FTestSetUp& TestSetUp = FTestSetUp::GetInstance();
		TestSetUp.Init();
		
		UUnitsFactory* Factory = TestSetUp.GameInstance->GetSubsystem<UUnitsFactory>();
		UUnitsCollection* UnitsCollection = Factory->CreateUnitCollection(TestSetUp.MilitaryBranch, TestSetUp.Country1);

		UUnitsCollectionGroup* UnitsCollectionGroup = Factory->CreateUnitCollectionGroup(TestSetUp.MilitaryBranch, TestSetUp.Country1,  { UnitsCollection });
		
		return UnitsCollectionGroup->GetMilitaryBranch() == TestSetUp.MilitaryBranch &&
			UnitsCollectionGroup->GetCountryOwner() == TestSetUp.Country1 &&
		    UnitsCollectionGroup->GetAll().Num() == 1 &&
			UnitsCollectionGroup->GetAll().Contains(UnitsCollection);
	}
		
}
