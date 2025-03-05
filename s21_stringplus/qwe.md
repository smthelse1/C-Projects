| Имя            | Библиотека      | Описание                                          | Тип возвращаемого значения | Возможные ошибки        | Дополнительная информация |
|---------------|----------------|--------------------------------------------------|--------------------------|-------------------------|---------------------------|
| open()        | unistd.h        | Открывает файл                                   | int (файловый дескриптор) | EACCES, ENOENT, EEXIST  |                           |
| read()        | unistd.h        | Читает данные из файла                          | ssize_t                  | EBADF, EFAULT, EINTR    |                           |
| write()       | unistd.h        | Записывает данные в файл                        | ssize_t                  | EBADF, EFAULT, EFBIG    |                           |
| close()       | unistd.h        | Закрывает файл                                  | int (0 при успехе)       | EBADF                   |                           |
| stat()        | sys/stat.h      | Получает информацию о файле                     | int                      | ENOENT, EACCES         |                           |
| mkdir()       | sys/stat.h      | Создает каталог                                 | int                      | EEXIST, EACCES         |                           |
| rmdir()       | unistd.h        | Удаляет пустой каталог                          | int                      | ENOENT, ENOTEMPTY      |                           |
| unlink()      | unistd.h        | Удаляет файл                                    | int                      | EACCES, EPERM          |                           |
| rename()      | stdio.h         | Переименовывает файл или каталог                | int                      | EACCES, ENOENT         |                           |
| access()      | unistd.h        | Проверяет доступность файла                     | int                      | EACCES, ENOENT         |                           |
| chmod()       | sys/stat.h      | Изменяет права доступа к файлу                  | int                      | EACCES, EPERM          |                           |
| fork()        | unistd.h        | Создает новый процесс                           | pid_t                    | EAGAIN, ENOMEM         |                           |
| exec()        | unistd.h        | Выполняет новый процесс                         | int                      | ENOENT, EACCES         |                           |
| wait()        | sys/wait.h      | Ожидает завершения дочернего процесса           | pid_t                    | ECHILD, EINTR          |                           |
| exit()        | stdlib.h        | Завершает процесс                               | void                     |                         |                           |
| getpid()      | unistd.h        | Получает ID текущего процесса                   | pid_t                    |                         |                           |
| getppid()     | unistd.h        | Получает ID родительского процесса              | pid_t                    |                         |                           |
| kill()        | signal.h        | Отправляет сигнал процессу                      | int                      | ESRCH, EPERM           |                           |
| sleep()       | unistd.h        | Приостанавливает выполнение процесса            | unsigned int             |                         |                           |
| nice()        | unistd.h        | Изменяет приоритет процесса                     | int                      | EPERM, EINVAL          |                           |
| setpriority() | sys/resource.h  | Устанавливает приоритет процесса               | int                      | EINVAL, ESRCH          |                           |
| signal()      | signal.h        | Устанавливает обработчик сигнала                | sighandler_t             | EINVAL                  |                           |
| sigaction()   | signal.h        | Устанавливает обработчик сигнала (расширенная) | int                      | EINVAL                  |                           |
| time()        | time.h          | Получает текущее время                          | time_t                   |                         |                           |
| gettimeofday()| sys/time.h      | Получает текущее время с точностью до микросекунд | int                      | EFAULT                  |                           |
| usleep()      | unistd.h        | Приостанавливает выполнение в микросекундах     | int                      | EINTR                   |                           |
| geteuid()     | unistd.h        | Получает эффективный UID                        | uid_t                    |                         |                           |
| getuid()      | unistd.h        | Получает реальный UID                           | uid_t                    |                         |                           |
| getegid()     | unistd.h        | Получает эффективный GID                        | gid_t                    |                         |                           |
| getgid()      | unistd.h        | Получает реальный GID                           | gid_t                    |                         |                           |
