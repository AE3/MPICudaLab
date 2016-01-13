#ifndef BLOCK_H
#define BLOCK_H

/**
 * Класс-замок для синхронизации
 */
class Block
{
public:

  /**
   * Конструктор класса вызывает Init
   * @see Block::Init
   */
  Block();

  /**
   * Открывает синхронизирующие замки
   */
   void Init();

   /**
    * Данным методом поток уведомляет о своей готовности к синхронизации
    * и ожидает остальных
    * @param ThreadID Индекс потока установленный мастер-потоком, мастер всегда 0.
    */
   void Barier(int ThreadID);

   /**
    * Синхронизация потоков относительно мастер-потока. Мастер может выполнять
    * любые монипуляции с данными между вызовами MasterBarier и Barier, потоки
    * будут в ожидании.
    * @see Block::Barier
    */
   void MasterBarier();

  ~Block();

private:

  /** Пока !true потоки будут ждать.*/
  bool Master;

  /** @see Block::Master */
  bool Solve1;

  /** @see Block::Master */
  bool Solve2;

};

#endif
