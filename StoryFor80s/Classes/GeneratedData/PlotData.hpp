/*
This file (PlotData.hpp) is generated
*/
#ifndef PlotData_hpp
#define PlotData_hpp
#include <map>
#include "BaseData.h"
#include <vector>
#include "DateData.hpp"
#include "PlotData.hpp"


class PlotData: public BaseData
{
private:
	static map<string, PlotData*>* p_sharedDictionary;
	string p_plotId;
	int p_priority;
	string p_condition;
	string p_dateId;
	bool p_repeatable;
	bool p_experienced;
	string p_plotStory;
	vector<string> p_selection_event;
	vector<string> p_selection_plotIdVector;
	vector<string> p_selection_text;
public:
	string getId() const;
	string getPlotId() const;
	int getPriority() const;
	string getCondition() const;
	DateData* getDateData() const;
	string getDateId() const;
	bool getRepeatable() const;
	bool getExperienced() const;
	void setExperienced(bool experienced);
	string getPlotStory() const;
	vector<string> getSelection_event() const;
	vector<PlotData*> getSelection_plotDataVector() const;
	vector<string> getSelection_plotIdVector() const;
	vector<string> getSelection_text() const;
	string getText() const;
	string description() const;
	static const map<string, PlotData*>* getSharedDictionary();
	static PlotData* getPlotDataById(const string& plotId);
	static bool saveData(const string & path);
	static bool loadData(const string & path);
	static bool clearData();
	void setFieldValue(const string & fieldName, const string & value);
	string getFieldValue(const string & fieldName) const;
	BaseData* getDataByField(const string & fieldName) const;
	vector<BaseData *> getFieldDataList(const string & fieldName) const;
};
#endif
