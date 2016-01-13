#ifndef MASTER_H
#define MASTER_H

#include <thread>
#include "block.h"

/**
 * Master класс обеспечивающий синхронизацию потоков, распределяет данные
 * между ними и выводит результат.
 */
class Master
{
public:

	/**
	 * Конструктор запускает обработку данных, в данной задаче, умножение массива
	 * чисел на число (факториал?).
	 * @param Data массив данных для обработки (ограничение 16ГБ).
	 * @param DataSize длинна данного массива.
	 */

	/**
	 *
	 */
	Master(std::string FileName);

	/**
	 * Деструктор проконтролирует корректное завершение потоков.
	 */
	~Master();

private:
	/** Указатель на массив данных
	 * @see Master::Master(int* Data, unsigned int DataSize) param Data
	 */
	int* Data;

	/** Длинна Data */
	unsigned int DataSize;

	/** Множитель для потоков */
	int N;

	/** Указатель на первый поток */
	std::thread* Thread1 = nullptr;

	/** Указатель на второй поток */
	std::thread* Thread2 = nullptr;

	/**
	 * Запуск потоков
	 */
	 void ThreadInit();

	/**
	 * Метод выполняющийся потоками. Умножает переданный фрагмент на число.
	 * @param ThreadID индекс потока.
	 */
	void Run(int ThreadID);

	/**
	 * Вывод массива в поток
	 */
	void Print();

  /**
	 * Основной метод класса отвечающий за синхронизацию потоков и вывод
	 * результатов.
	 */
	void Synchronize();

	/**
	 * Структура читаемого файла:
	 * Длинна массива
	 * Максимальный множитель
	 * Данные
	 * @param FileName
	 */
	void ReadFile(std::string FileName);

  /**
	 * @see Block
	 */
	Block SyncBlock;
};

#endif
