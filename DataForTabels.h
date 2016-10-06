#ifndef DATAFORTABLES_H
#define DATAFORTABLES_H

#include <vector>
using std::vector;

// �������� ������ ��� �������� ������
class DataForTabels
{
public:

	DataForTabels(){}
	void getDataForTabels(TMemo *memo1, TMemo *memo2, TMemo *memo3)
		{


			alternativesCount = memo1->Lines->Count;
		   criteriaCount = memo2->Lines->Count;
		   TableCount = criteriaCount;
		   expertsCount =  memo3->Lines->Count;


		   for(int i = 0; i < alternativesCount; i++)
		   {
			  alternatives.push_back(memo1->Lines->Strings[i]);
		   }

		   for(int i = 0; i < criteriaCount; i++)
		   {
			  criteria.push_back(memo2->Lines->Strings[i]);
		   }

		   for(int i = 0; i < expertsCount; i++)
		   {
			  experts.push_back(memo3->Lines->Strings[i]);
		   }
		}

		// ������� ���������� ������ �� ���������
		int getTableCount()
		{
			return TableCount;
		}

		// ������� ���������� ���������
		int getCriteriaCount()
		{
			return criteriaCount;
		}

		//�������� ���������� �����������
		int getAlternativesCount()
		{
			return alternativesCount;
		}

		// �������� ���������� ���������
		int getExpertsCount()
		{
			return expertsCount;
		}

		// �������� ��� ��������
		UnicodeString getExpertName(int i)
		{
			return experts[i];
		}

		// �������� �������� �������� �� �������
		UnicodeString getCriteriaName(int i)
		{
			return criteria[i];
		}

		// �������� �������� ����������� �� �������
		UnicodeString getAlternativesName(int i)
		{
			return alternatives[i];
		}



		void Clear()
		{
			vector<UnicodeString>().swap(criteria);
			vector<UnicodeString>().swap(alternatives);
			vector<UnicodeString>().swap(experts);

			criteriaCount = 0;
			alternativesCount = 0;
			expertsCount = 0;
			TableCount= 0;
		}

private:
	vector<UnicodeString> criteria;
	vector<UnicodeString> alternatives;
	vector<UnicodeString> experts;

	int criteriaCount;
	int alternativesCount;
	int expertsCount;
	int TableCount;
};
#endif