#include "pullData.h"
#include <iostream>
#include <fstream>

void pullData::fetchData(const string& path)
{
	cout << "Генерация текстовых данных..." << endl;

	string dummy_json = R"([
		{"spec_name": "Математика", "class_work_mark": 5},
		{"spec_name": "Математика", "class_work_mark": 4},
		{"spec_name": "Физика", "class_work_mark": null},
		{"spec_name": "Физика", "class_work_mark": 3},
		{"spec_name": "Русский язык", "class_work_mark": 5}
	])";

	ofstream out(path);
	if (out.is_open())
	{
		out << dummy_json;
		out.close();
		cout << "Данные сохранены в" << path << endl;
	}
	else
	{
		cerr << "Ошибка при записи файла." << endl;
	}
}