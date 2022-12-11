/* Do not modify this file */
#ifndef LOGGING_H
#define LOGGING_H

#define LOG_FG      0
#define LOG_BG      1

#define LOG_STATE_READY      0
#define LOG_STATE_RUNNING    1
#define LOG_STATE_SUSPENDED  2
#define LOG_STATE_FINISHED   3
#define LOG_STATE_KILLED     4

#define LOG_CMD_SUSPEND 0
#define LOG_CMD_RESUME  1
#define LOG_CMD_KILL  2

#define LOG_FILE_PIPE "(pipe)"

#define LOG_REDIR_IN   0
#define LOG_REDIR_OUT  1

#define LOG_TERM       0
#define LOG_TERM_SIG   1
#define LOG_RESUME     2
#define LOG_SUSPEND    3
#define LOG_START      4

void log_kitc_intro();
void log_kitc_prompt();
void log_kitc_help();
void log_kitc_quit();
void log_kitc_num_tasks(int num_tasks);
void log_kitc_task_info(int task_num, int status, int exit_code, int pid, const char *cmd);
void log_kitc_task_init(int task_num, const char *cmd);
void log_kitc_task_num_error(int task_num);
void log_kitc_purge(int task_num);
void log_kitc_status_error(int task_num, int status);
void log_kitc_status_change(int task_num, int pid, int type, const char *cmd, int transition);
void log_kitc_exec_error(const char *line);
void log_kitc_sig_sent(int sig_type, int task_num, int pid);
void log_kitc_file_error(int task_num, const char *file);
void log_kitc_redir(int task_num, int redir_type, const char *file);
void log_kitc_pipe(int task_num1, int task_num2);
void log_kitc_pipe_error(int task_num);
void log_kitc_ctrl_c();
void log_kitc_ctrl_z();

#endif /*LOGGING_H*/
