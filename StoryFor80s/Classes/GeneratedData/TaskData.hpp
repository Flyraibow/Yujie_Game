/*
This file (TaskData.hpp) is generated
*/
#ifndef TaskData_hpp
#define TaskData_hpp
#include <map>
#include "BaseData.h"
#include "SelectableScheduleData.hpp"


class TaskData: public BaseData
{
private:
	static map<string, TaskData*>* p_sharedDictionary;
	string p_itemId;
	bool p_isOnGoing;
	bool p_failed;
	int p_startedYear;
	int p_startedMonth;
	bool p_isTimeLimited;
	int p_limitedMonth;
	int p_leftMonth;
	string p_failCondition;
	string p_forbiddenScheduleId;
	string p_successCondition;
	string p_failedEvent;
	string p_successEvent;
public:
	string getId() const;
	string getItemId() const;
	string getName() const;
	string getDescription() const;
	bool getIsOnGoing() const;
	void setIsOnGoing(bool isOnGoing);
	bool getFailed() const;
	void setFailed(bool failed);
	int getStartedYear() const;
	void setStartedYear(int startedYear);
	int getStartedMonth() const;
	void setStartedMonth(int startedMonth);
	bool getIsTimeLimited() const;
	int getLimitedMonth() const;
	int getLeftMonth() const;
	void setLeftMonth(int leftMonth);
	string getFailCondition() const;
	SelectableScheduleData* getForbiddenScheduleData() const;
	string getForbiddenScheduleId() const;
	string getSuccessCondition() const;
	string getFailedEvent() const;
	string getSuccessEvent() const;
	string description() const;
	static const map<string, TaskData*>* getSharedDictionary();
	static TaskData* getTaskDataById(const string& itemId);
	static bool saveData(const string & path);
	static bool loadData(const string & path);
	static bool clearData();
	void setFieldValue(const string & fieldName, const string & value);
	string getFieldValue(const string & fieldName) const;
	BaseData* getDataByField(const string & fieldName) const;
	vector<BaseData *> getFieldDataList(const string & fieldName) const;
};
#endif
