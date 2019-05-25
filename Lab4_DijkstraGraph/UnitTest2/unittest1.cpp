#include "stdafx.h"
#include "CppUnitTest.h"
#include"c:\Users\Андрей\Desktop\Lab4_DijkstraGraph\Lab4_DijkstraGraph\Dijkstra.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest2
{		
	TEST_CLASS(UnitTest1)
	{private:
		Map<string, data_flight>TestMap;
		data_flight Berlin;
		data_flight Stambul;
		data_flight Moscow;
		data_flight Vladivostok;
		data_flight Tokyo;
		flights BM, BS, SV, VS;
		flights SB, MB,SM,MV,MS,VM,ST,TS,MT,TM,VT,TV;

		
	public:
		

		TEST_METHOD(BerlinStambul)
		{
			int t = 10;
			string t1 = "Berlin";
			string t2 = "Stambul";
			string t3 = "Moscow";
			BM.city = "Moscow";
			BM.cost = 20;
			BS.city = "Stambul";
			BS.cost = 10;
			SB.city = "Berlin";
			SB.cost = 34;
			MB.city = "Berlin";
			MB.cost = 30;
			Berlin.adjency.push_back(BM);
			Berlin.adjency.push_back(BS);
			Stambul.adjency.push_back(SB);
			Moscow.adjency.push_back(MB);
			TestMap.insert(t1, Berlin);
			TestMap.insert(t2, Stambul);
			TestMap.insert(t3, Moscow);
			int i = Find_flight_cost(t1, t2, &TestMap);
			Assert::AreEqual(t, i);
		}

		TEST_METHOD(SizeofMap)
		{
			int t = 10;
			string t1 = "Berlin";
			string t2 = "Stambul";
			string t3 = "Moscow";
			BM.city = "Moscow";
			BM.cost = 20;
			BS.city = "Stambul";
			BS.cost = 10;
			SB.city = "Berlin";
			SB.cost = 34;
			MB.city = "Berlin";
			MB.cost = 30;
			Berlin.adjency.push_back(BM);
			Berlin.adjency.push_back(BS);
			Stambul.adjency.push_back(SB);
			Moscow.adjency.push_back(MB);
			TestMap.insert(t1, Berlin);
			TestMap.insert(t2, Stambul);
			TestMap.insert(t3, Moscow);
			int i = TestMap.get_size();
			Assert::AreEqual(3, i);
		}

		TEST_METHOD(StambulTokyo)
		{
			int t = 7;
			string t1 = "Berlin";
			string t2 = "Stambul";
			string t3 = "Moscow";
			string t4 = "Vladivostok";
			string t5 = "Tokyo";
			BM.city = "Moscow";
			BM.cost = 20;
			BS.city = "Stambul";
			BS.cost = 10;
			SB.city = "Berlin";
			SB.cost = 34;
			MB.city = "Berlin";
			MB.cost = 30;
			MS.city = "Stambul";
			MS.cost = 9;
			SM.city = "Moscow";
			SM.cost = 1;
			SV.city = "Vladivostok";
			SV.cost = 2;
			VS.city = "Stambul";
			VS.cost = 3;
			MT.city = "Tokyo";
			MT.cost = 15;
			TM.city = "Moscow";
			TM.cost = 5;
			VT.city = "Tokyo";
			VT.cost = 5;
			TV.city = "Vladivostok";
			TV.cost = 5;
			MV.city = "Vladivostok";
			MV.cost = 3;
			VM.city = "Moscow";
			VM.cost = 2;
			ST.city = "Tokyo";
			ST.cost = 40;
			TS.city = "Stambul";
			TS.cost = 12;
			Berlin.adjency.push_back(BM);
			Berlin.adjency.push_back(BS);
			Stambul.adjency.push_back(SB);
			Stambul.adjency.push_back(SM);
			Stambul.adjency.push_back(SV);
			Moscow.adjency.push_back(MB);
			Moscow.adjency.push_back(MS);
			Moscow.adjency.push_back(MV);
			Moscow.adjency.push_back(MT);
			Vladivostok.adjency.push_back(VS);
			Vladivostok.adjency.push_back(VM);
			Vladivostok.adjency.push_back(VT);
			Tokyo.adjency.push_back(TM);
			Tokyo.adjency.push_back(TV);
			TestMap.insert(t1, Berlin);
			TestMap.insert(t2, Stambul);
			TestMap.insert(t3, Moscow);
			TestMap.insert(t4, Vladivostok);
			TestMap.insert(t5, Tokyo);

			int i = Find_flight_cost(t2, t5, &TestMap);
			Assert::AreEqual(t, i);
		}
	};
}