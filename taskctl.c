/* This is the only file you should update and submit. */

/* Fill in your Name and GNumber in the following two comment fields
 * Name:KIM DUONG
 * GNumber:  G01177228
 */

#include <sys/wait.h>
#include "taskctl.h"
#include "parse.h"
#include "util.h"
#include <fcntl.h>
#include <unistd.h>
#include<stdio.h>



//constant 
#define DEBUG 1


// uncomment if you want to use any of these:


#define NUM_INSTRUCTIONS 10

static const char *task_path[] = { "./", "/usr/bin/", NULL };
static const char *instructions[] = { "quit", "help", "list", "purge", "exec", "bg", "kill", "suspend", "resume", "pipe", NULL};


typedef struct status_command{
        char cmd_ptr[255];
	char type[50];
        int pid;
        int status;
        char * array_argv[MAXARGS+1];
        int exit_code;
}status_command;
 status_command array_status[255];
char **task[255]={NULL};
int flag=0;
int status1=-1;
int task_num_bg=-1;
int status2=-1;
pid_t child_bg=0;
int kill1=0;
pid_t pipe_child_a=0;
int pipe_child=0;
pid_t pipe_child_a_check=0;
int kill_tasknum=0;
char script_bg[100]={0};
char script_pipe[100]={0};
int kill_pid=0;
char kill_cmd[100]={0};
int suspend=0;
int resume=0;
int resume1=0;
int forground_pid1=-1;
int forground_pid2=-1;
int forground_pid3=-1;
int sigint =0;
int sigstop=0;
int pipechild1=0;
int exec =0;

void handler2(){

	if(forground_pid1==-1){
}else{
	sigstop=1;
	log_kitc_ctrl_z();
	if (forground_pid1 !=-1){
        kill(forground_pid1,SIGTSTP);

}

}}
int sigint1=0;
void handler1(){

if(forground_pid1==-1 ){
}else{
log_kitc_ctrl_c();
sigint=1;
sigint1=1;
if (forground_pid1 !=-1){
	kill(forground_pid1,SIGINT);
	
}
}
}
void checkpid(int pid){
  if (pid>0){     int k=0;
                         for(int i=1;i<255;i++){
                                 if ((array_status[i].pid==pid)){
                                         k=i;
                                         break;
                                        }

                         }
                         if(strcmp(array_status[k].type,"fg")==0){

                         if( sigstop==0&& sigint==0){
                                 int status_exit1 =WEXITSTATUS(status2);
                               log_kitc_status_change(k, pid,0,array_status[k].cmd_ptr,0);

                               array_status[k].status=3;
                               array_status[k].exit_code=status_exit1;
                               forground_pid1=-1;
                              }else{
                                       if (sigint ==1){
                                          log_kitc_status_change(k,array_status[k].pid ,0,array_status[k].cmd_ptr,1);
                                          sigint=0;
                                          sigint1=0;

                                          forground_pid1=-1;
                                          array_status[k].status=4;
                                          int status_exit1 =WEXITSTATUS(status2);
                                           array_status[k].exit_code=status_exit1;



                                }
                                       if (sigstop ==1){
                                          log_kitc_status_change(k,array_status[k].pid ,0,array_status[k].cmd_ptr,3);
                                          sigstop=0;
                                          forground_pid1=-1;
                                          array_status[k].status=2;
                                          int status_exit1=WEXITSTATUS(status2);
                                           array_status[k].exit_code=status_exit1;
                                       }        }


                                }else{
                                        array_status[k].exit_code=WEXITSTATUS(status2);
                if (kill1== 1){
                  log_kitc_status_change(k,array_status[k].pid,1,array_status[k].cmd_ptr,1);
                   array_status[k].status=4;

                    kill1=0;
		      }else if(suspend==1){
                         log_kitc_status_change(k,array_status[k].pid,1,array_status[k].cmd_ptr,3);
                         array_status[k].status=2;
                         suspend=0;


                }
                else{
                  array_status[k].status=3;
                log_kitc_status_change(k,array_status[k].pid,1,array_status[k].cmd_ptr,0);
                }



                        }

}}
void handler(int sig) {
			pid_t pid=-1;
       if(exec==0){	
	 pid= waitpid(-1,&status2,WNOHANG);	
     
	if (pid>0){	int k=0;
			 for(int i=1;i<255;i++){
				 if ((array_status[i].pid==pid)){
					 k=i;
					 break;
					} }
			 if(strcmp(array_status[k].type,"fg")==0){

			 if( sigstop==0&& sigint==0){ 
				 int status_exit1 =WEXITSTATUS(status2);
                               log_kitc_status_change(k, pid,0,array_status[k].cmd_ptr,0);
                               
                               array_status[k].status=3;
                               array_status[k].exit_code=status_exit1;
                               forground_pid3=-1;
                              }else{
                                       if (sigint ==1){
                                          log_kitc_status_change(k,array_status[k].pid ,0,array_status[k].cmd_ptr,1);
                                          sigint=0;
                                          sigint1=0;
					 
                                          forground_pid1=-1;
                                          array_status[k].status=4;
                                          int status_exit1 =WEXITSTATUS(status2);
                                           array_status[k].exit_code=status_exit1;



                                }
                                       if (sigstop ==1){
                                          log_kitc_status_change(k,array_status[k].pid ,0,array_status[k].cmd_ptr,3);
                                          sigstop=0;
                                          forground_pid1=-1;
                                          array_status[k].status=2;
                                          int status_exit1=WEXITSTATUS(status2);
                                           array_status[k].exit_code=status_exit1;
                                       }        }
			  
                                         
			  	}else{
					array_status[k].exit_code=WEXITSTATUS(status2);
		if (kill1== 1){
                  log_kitc_status_change(k,array_status[k].pid,1,array_status[k].cmd_ptr,1);
		   array_status[k].status=4;
		    
                    kill1=0;
		   
		}else if(suspend==1){
			 log_kitc_status_change(k,array_status[k].pid,1,array_status[k].cmd_ptr,3);
			 array_status[k].status=2;
			 suspend=0;
			 

		}	
		else{
                  array_status[k].status=3;
		log_kitc_status_change(k,array_status[k].pid,1,array_status[k].cmd_ptr,0);
		}
	
	
			 
                   	}
	
	}
	}
}
	
	
	 
int check_pipe(status_command array_status[],int k,int m){
	int p[2];
	int l=pipe(p);
	if (l<0){
                log_kitc_file_error(k, array_status[k].cmd_ptr);
		return 1;
	}
  
        if (!(pipe_child_a_check=fork())){
                    //child A does not need to use read-end
                    close(p[0]);
                    dup2(p[1],STDOUT_FILENO);
		    close(p[1]);
                      char try1[100];
                      char instruct_command[100];
                          strcpy(instruct_command,array_status[k].array_argv[0]);
      			  strcpy(try1,task_path[0]);
                          strcat(try1,instruct_command);
                          execv(try1,array_status[k].array_argv);
                          char try2[100];
                          strcpy(try2,task_path[1]);
                          strcat(try2,instruct_command);
                          execv(try2,array_status[k].array_argv);
			  log_kitc_exec_error(array_status[k].cmd_ptr);
			  exit(1);
     	}
	int pid2=0;
	if(!(pid2=fork())){
                                           close(p[1]);// the child B does not need the write end
                                           dup2(p[0],STDIN_FILENO);
					   close(p[0]);
                                           char try1[100];
                                           char instruct_command[100];
                                           strcpy(instruct_command,array_status[m].array_argv[0]);
                                           strcpy(try1,task_path[0]);
                                           strcat(try1,instruct_command);
					  int  file_src_out = open("outcheck.txt",O_WRONLY|O_TRUNC|O_CREAT,0600);
					  dup2(file_src_out,STDOUT_FILENO);
                                           execv(try1,array_status[m].array_argv);
                                           char try2[100];
                                           strcpy(try2,task_path[1]);
                                           strcat(try2,instruct_command);
                                           execv(try2,array_status[m].array_argv);
					   log_kitc_exec_error(array_status[m].cmd_ptr);
					   exit(1);
       	}
                                          close(p[0]);
                                          close(p[1]);
                                          int status_exit;
					  int status_exit1;
                                          pid_t pid = waitpid(-1,&status_exit,0);
					  pid_t pid1 = waitpid(-1,&status_exit1,0);
                               int exit =WEXITSTATUS(status_exit);
			       int exit1 =WEXITSTATUS(status_exit1);

                               if (exit==0&&exit1==0){
				       return 0;
			       }else{
				       return 1;
				   }}

/* The entry of your task controller program */
int main(){
    struct sigaction sa,sa1;
    struct sigaction sa2;
    memset(&sa2,0,sizeof(sa2));
    memset(&sa,0,sizeof(sa));
    memset(&sa1,0,sizeof(sa1));
    sa.sa_handler = handler;
    sa1.sa_handler = handler1;
    sa2.sa_handler=handler2;
    sigaction(SIGCHLD,&sa,NULL);
    sigaction(SIGTSTP,&sa2,NULL);
    sigaction(SIGINT,&sa1,NULL);
    char cmdline[MAXLINE];        /* Command line */
    char *cmd = NULL;
    
    for (int i=0;i<255;i++){
            for (int m =0;m<(MAXARGS+1);m++){
                    array_status[i].array_argv[m]=NULL;
                }
            array_status[i].pid=-1;
            array_status[i].exit_code=-1;
            array_status[i].status=-1;
            memset(array_status[i].cmd_ptr,'\0', sizeof(array_status[i].cmd_ptr));
            memset(array_status[i].type,'\0', sizeof(array_status[i].type)); }
           
    int num=0;
/* Intial Prompt and Welcome */
    log_kitc_intro();
    log_kitc_help();
   
    /* Shell looping here to accept user command and execute */
    while (1) {
	   
		
	   
		    
		   
		   
	     

        char *argv[MAXARGS+1];        /* Argument list */
        Instruction inst;           /* Instruction structure: check parse.h */

        /* Print prompt */
        log_kitc_prompt();

        /* Read a line */
        // note: fgets will keep the ending '\n'
	errno = 0;
        if (fgets(cmdline, MAXLINE, stdin) == NULL) {
            if (errno == EINTR) {
                continue;
            }
            exit(-1);
        }

        if (feof(stdin)) {  /* ctrl-d will exit text processor */
          exit(0);
        }

        /* Parse command line */
        if (strlen(cmdline)==1)   /* empty cmd line will be ignored */
          continue;     

        cmdline[strlen(cmdline) - 1] = '\0';        /* remove trailing '\n' */

        cmd = malloc(strlen(cmdline) + 1);          /* duplicate the command line */
        snprintf(cmd, strlen(cmdline) + 1, "%s", cmdline);
	    
        /* Bail if command is only whitespace */
        if(!is_whitespace(cmd)) {
            initialize_command(&inst, argv);    /* initialize arg lists and instruction */
            parse(cmd, &inst, argv);            /* call provided parse() */

            if (0) {  /* display parse result, redefine DEBUG to turn it off */
                debug_print_parse(cmd, &inst, argv, "main (after parse)");
	    }

            /* After parsing: your code to continue from here */
            /*================================================*/
              
	//list all the tasks and their information 
	    if (strcmp("list",cmd)==0){
                     log_kitc_num_tasks(num);
                     for (int i=1; i<255;i++){
                             if (task[i] != NULL){
                                     log_kitc_task_info(i,array_status[i].status,array_status[i].exit_code,array_status[i].pid,array_status[i].cmd_ptr);



                            }

                     }
              }
	    char argument[100]={0};


	   
	    strcpy(argument,inst.instruct);

	    if (strcmp(argument,"help")==0){
		    log_kitc_help();
		   }
	    /*kill TASKNUM: terminates the process associated with Task TASKNUM using SIGINT.*/
	    if (strcmp(argument,"kill")==0){
		    if (task[inst.num] ==NULL){
			    log_kitc_task_num_error(inst.num);
		   }else{
			   if (array_status[inst.num].status==0 || array_status[inst.num].status == 3 || array_status[inst.num].status==4){
				   log_kitc_status_error(inst.num,array_status[inst.num].status);

			}else{
				
                                 kill1=1;
				 kill_pid=0;
				log_kitc_sig_sent(2,inst.num,array_status[inst.num].pid);	
				kill(array_status[inst.num].pid,SIGINT);
				int status_kill;
                                int kill_pid1;
				if (array_status[inst.num].status==1){
				 kill_pid1=waitpid(array_status[inst.num].pid,&status_kill,0);
				  if (strcmp(array_status[inst.num].type,"fg")==0){
                                        log_kitc_status_change(inst.num,array_status[inst.num].pid ,0,array_status[inst.num].cmd_ptr,1);
                                        array_status[inst.num].exit_code=WEXITSTATUS(status_kill);
                                        kill1=0;
                                       exec=0;

                                }else{
                                         log_kitc_status_change(inst.num,array_status[inst.num].pid ,1,array_status[inst.num].cmd_ptr,1);
                                          array_status[inst.num].exit_code=WEXITSTATUS(status_kill);
                                          kill1=0;
                                          exec=0;
                                }

				}else{
				 kill_pid1=waitpid(array_status[inst.num].pid,&status_kill,WNOHANG);
				  if (strcmp(array_status[inst.num].type,"fg")==0){
                                        log_kitc_status_change(inst.num,array_status[inst.num].pid ,0,array_status[inst.num].cmd_ptr,1);
                                        array_status[inst.num].exit_code=0;
                                        kill1=0;
                                       exec=0;

                                }else{
                                         log_kitc_status_change(inst.num,array_status[inst.num].pid ,1,array_status[inst.num].cmd_ptr,1);
                                          array_status[inst.num].exit_code=0;
                                          kill1=0;
                                          exec=0;
                                
				}}


				 array_status[inst.num].status=4;
				 }
			   
	          }
            }
	    /*resumes the suspended process associated with Task TASKNUM using SIGCONT */
	     if (strcmp(argument,"resume")==0){
                    if (task[inst.num] ==NULL){
                            log_kitc_task_num_error(inst.num);
                   }else{
                           if (array_status[inst.num].status==0 || array_status[inst.num].status == 3 || array_status[inst.num].status==4){
                                   log_kitc_status_error(inst.num,array_status[inst.num].status);

                        }else{
				
				
                                  strcpy(array_status[inst.num].type,"fg");
                                forground_pid1=array_status[inst.num].pid;
				log_kitc_sig_sent(1,inst.num,array_status[inst.num].pid);
                                
                               int  kill_pid1=array_status[inst.num].pid;
                                
                                array_status[inst.num].status=1;
				
                               
                                log_kitc_status_change(inst.num,kill_pid1,0,array_status[inst.num].cmd_ptr,2);
                                kill(array_status[inst.num].pid,SIGCONT);
				pid_t pid2=-1;
				pid_t pid=-1;
				int status_exit;
				
				pid2= waitpid(-1,&status_exit,0);
					
				
			
				pid= waitpid(-1,&status_exit,0);
		
				if(pid== array_status[inst.num].pid){
                              if (  sigstop==0 && sigint==0){
                               int status_exit1 =WEXITSTATUS(status_exit);
                               log_kitc_status_change(inst.num, pid,0,array_status[inst.num].cmd_ptr,0);
                              forground_pid1=-1;
                               array_status[inst.num].status=3;
                               array_status[inst.num].exit_code=status_exit1;


                              }}else
                        {     if(pid==-1){
                                                 if (sigstop ==1){
                                          log_kitc_status_change(inst.num,array_status[inst.num].pid ,0,array_status[inst.num].cmd_ptr,3);
                                          sigstop=0;
                                          forground_pid1=-1;
                                          array_status[inst.num].status=2;


                                       }

                                         }

                           else{  int k=0;     
				   for(int i=1;i<255;i++){
                                        if(array_status[i].pid==pid){
                                                k=i;
                                                
                                        }
                                }
                                array_status[k].exit_code=WEXITSTATUS(status_exit);
                if (kill1== 1){
                  log_kitc_status_change(k,array_status[k].pid,1,array_status[k].cmd_ptr,1);
                   array_status[k].status=4;

                    kill1=0;

                }else if(suspend==1){
                         log_kitc_status_change(k,array_status[k].pid,1,array_status[k].cmd_ptr,3);
                         array_status[k].status=2;
                         suspend=0;


                }
                else{
                  array_status[k].status=3;
                log_kitc_status_change(k,array_status[k].pid,1,array_status[k].cmd_ptr,0);
                }

           }
                        }				
				


				 }

                  }
            }
	     /*suspend TASKNUM: suspends the process associated with Task TASKNUM using SIGTSTP.*/
	    if (strcmp(argument,"suspend")==0){
		     if (task[inst.num] ==NULL){
                            log_kitc_task_num_error(inst.num);
                   }else{
			   if (array_status[inst.num].status==0 || array_status[inst.num].status == 3 || array_status[inst.num].status==4){
                                   log_kitc_status_error(inst.num,array_status[inst.num].status);

                        }else{
		
		               
		       		log_kitc_sig_sent(0,inst.num,array_status[inst.num].pid);
				 kill_pid=0;
                                kill_tasknum=inst.num;
                              int   kill_pid1=array_status[inst.num].pid;
                                strcpy(kill_cmd,array_status[inst.num].cmd_ptr);
                               
                                
				
               
				 
			       kill(array_status[inst.num].pid,SIGTSTP);
			       if(array_status[inst.num].status==1){
				        int pid_kill1= waitpid(-1,NULL,0);

				 }else{
					  int pid_kill1= waitpid(-1,NULL,WNOHANG);
			    }
			     
				 if (strcmp(array_status[inst.num].type,"fg")==0){
                                        log_kitc_status_change(inst.num,array_status[inst.num].pid ,0,array_status[inst.num].cmd_ptr,3);
                               array_status[inst.num].status=2;        

                                }else{
                                         log_kitc_status_change(inst.num,array_status[inst.num].pid ,1,array_status[inst.num].cmd_ptr,3);
					 array_status[inst.num].status=2;
                                          
                                         
                                }

			}
		}

	    }
	    /*• Parent process P has two children, A and B.
             • A wants to send data to B.
             • P creates a pipe before forking A or B; thus, both A and B gain access to the pipe. • A redirects its output to the write-end of the pipe and closes its read-end.
• B redirects its input from the read-end of the pipe and closes its write-end.
• P closes both its read-end and write-end, because it is not directly using either.
• Now, any output from A gets sent as input to B.    */
	    if (strcmp(argument,"pipe")==0){
		   int p[2];
		   
                   int status_exit1;
		   int status_exit;
		  

		 
		    if (inst.num2== inst.num){
			 log_kitc_pipe_error(inst.num);

		}else if(task[inst.num] ==NULL|| task[inst.num2] ==NULL)
{
      if(task[inst.num] ==NULL) {
	      log_kitc_task_num_error(inst.num);
      }
       if(task[inst.num2] ==NULL) {
              log_kitc_task_num_error(inst.num2);
      }

}else{
			  
		if (array_status[inst.num].status==1 || array_status[inst.num].status==2 || array_status[inst.num2].status==1||array_status[inst.num2].status==2){

			  if (array_status[inst.num].status==1)
                                                     { log_kitc_status_error(inst.num,1);

                                                        }
                                                     if(array_status[inst.num].status==2){
                                                                log_kitc_status_error(inst.num,2);

                                                        }
						      if (array_status[inst.num2].status==1)
                                                     { log_kitc_status_error(inst.num2,1);

                                                        }
                                                     if(array_status[inst.num2].status==2){
                                                                log_kitc_status_error(inst.num2,2);

                                                        }
		}else if(check_pipe(array_status, inst.num,inst.num2)==1){
			
		}	else{
			
		   array_status[inst.num].status=1;
		   pipe(p);
		   log_kitc_pipe(inst.num, inst.num2);
		   strcpy(kill_cmd,array_status[inst.num].cmd_ptr);
		   kill_tasknum= inst.num;
                  
		  array_status[inst.num].status=1;
		  strcpy(array_status[inst.num].type,"bg");
              
		   if (!(array_status[inst.num].pid=kill_pid=fork())){
                    //child A does not need to use read-end
		    setpgid(0,0);
		    close(p[0]);
                    dup2(p[1],STDOUT_FILENO);
		    
		    close(p[1]);
                     log_kitc_status_change(inst.num,getpid(),1,array_status[inst.num].cmd_ptr,4);
                      char try1[100];
                      char instruct_command[100];
		        strcpy(instruct_command,array_status[inst.num].array_argv[0]);           
	       		strcpy(try1,task_path[0]);
                          strcat(try1,instruct_command);
			   
                           execv(try1,array_status[inst.num].array_argv);
                           char try2[100];
                           strcpy(try2,task_path[1]);
                           strcat(try2,instruct_command);
                           execv(try2,array_status[inst.num].array_argv);   }else{
		   
		 int  pid2=0;
		 
                
				 array_status[inst.num2].status=1;
		                          	 
				  
				  strcpy(array_status[inst.num2].type,"fg");
		             		 if(!(forground_pid1=array_status[inst.num2].pid=pid2=fork())){
						 setpgid(0,0);
					 close(p[1]);// the child B does not need the write end 
					 dup2(p[0],STDIN_FILENO);
                                         close(p[0]);
					  log_kitc_status_change(inst.num2,getpid(),0,array_status[inst.num2].cmd_ptr,4);
					   char try1[100];
                                           char instruct_command[100];
                    strcpy(instruct_command,array_status[inst.num2].array_argv[0]);
		     strcpy(try1,task_path[0]);
                                   strcat(try1,instruct_command);
				     
                                   execv(try1,array_status[inst.num2].array_argv);
                                   char try2[100];
                                   strcpy(try2,task_path[1]);
                                   strcat(try2,instruct_command);
                                    execv(try2,array_status[inst.num2].array_argv);
				 }else{
	                	  close(p[0]);
			          close(p[1]);
				 
					  
				int pid12=waitpid(-1,&status_exit,0);
			      	
				   int pid13=waitpid(-1,&status_exit1,0);
				   
                                               
		     // waitpid(pipe_child_a,&status_exit,0);
                           if(pid12== array_status[inst.num2].pid){
                              if (  sigstop==0 && sigint==0){
                               int status_exit1 =WEXITSTATUS(status_exit);
                               log_kitc_status_change(inst.num2, pid12,0,array_status[inst.num2].cmd_ptr,0);
                              forground_pid1=-1;
                               array_status[inst.num2].status=3;
                               array_status[inst.num2].exit_code=status_exit1;
                                  }}else {     if(pid12<=0){
                                                 if (sigstop ==1){
                                          log_kitc_status_change(inst.num2,array_status[inst.num2].pid ,0,array_status[inst.num2].cmd_ptr,3);
                                          sigstop=0;
                                          forground_pid1=-1;
                                          array_status[inst.num2].status=2;
                                                }

                                         }

                           else{       int k=0;
				   for(int i=1;i<255;i++){
                                        if(array_status[i].pid==pid12){
                                                k=i;
                                                
                                        }
                                }
                                array_status[k].exit_code=WEXITSTATUS(status_exit);
                if (kill1== 1){
                  log_kitc_status_change(k,array_status[k].pid,1,array_status[k].cmd_ptr,1);
                   array_status[k].status=4;

                    kill1=0;

                }else if(suspend==1){
                         log_kitc_status_change(k,pid12,1,array_status[k].cmd_ptr,3);
                         array_status[k].status=2;
                         suspend=0;
	       	} else{
                  array_status[k].status=3;
                log_kitc_status_change(k,pid12,1,array_status[k].cmd_ptr,0);
                }

           }
                        }
	 if(pid13== array_status[inst.num2].pid){
                              if (  sigstop==0 && sigint==0){
                               int status_exit12 =WEXITSTATUS(status_exit1);
                               log_kitc_status_change(inst.num2, pid13,0,array_status[inst.num2].cmd_ptr,0);
                              forground_pid1=-1;
                               array_status[inst.num2].status=3;
                               array_status[inst.num2].exit_code=status_exit12;
                                  }}else {     if(pid13<=0){
                                                 if (sigstop ==1){
                                          log_kitc_status_change(inst.num2,array_status[inst.num2].pid ,0,array_status[inst.num2].cmd_ptr,3);
                                          sigstop=0;
                                          forground_pid1=-1;
                                          array_status[inst.num2].status=2;
                                                }
        
                                         } else{       int k=0;
                                   for(int i=1;i<255;i++){
                                        if(array_status[i].pid==pid13){
                                                k=i;
                                                 
                                        }
                                }
                                array_status[k].exit_code=WEXITSTATUS(status_exit1);
                if (kill1== 1){
                  log_kitc_status_change(k,array_status[k].pid,1,array_status[k].cmd_ptr,1);
                   array_status[k].status=4;

                    kill1=0;

                }else if(suspend==1){
                         log_kitc_status_change(k,pid12,1,array_status[k].cmd_ptr,3);
                         array_status[k].status=2;
                         suspend=0;
                } else{
                  array_status[k].status=3;
                log_kitc_status_change(k,pid12,1,array_status[k].cmd_ptr,0);
                }

           }
                        }
			      

				  }
	 

			   }	}

		}

   }
         /* The command is the external command associated with task TASKNUM */
	      if (strcmp(argument,"exec")==0){
                        int status_exit;
                        if (task[inst.num] ==NULL){
                                                log_kitc_task_num_error(inst.num);

                                        }else{
                                             if (array_status[inst.num].status==0 || array_status[inst.num].status==3 || array_status[inst.num].status==4){
                                        int file_src_in=0;
                                        int file_src_out=0;

                                         if (inst.infile !=NULL){
                      file_src_in = open(inst.infile,O_RDONLY);
                      }
                                         if (inst.outfile != NULL){
						 file_src_out = open(inst.outfile,O_WRONLY|O_TRUNC|O_CREAT,0600);


                   }  if (file_src_in>=0 && file_src_out>=0){
                           array_status[inst.num].status=1;


                      }
					 
		
		          array_status[inst.num].status=1;
			  strcpy(array_status[inst.num].type,"fg");
			 
                          exec =1;
                          if (!(forground_pid1=array_status[inst.num].pid=fork())){ 
     				setpgid(0,0);
				  
                     if ( inst.infile !=NULL){

                     if (file_src_in <0){
                             log_kitc_file_error(inst.num, inst.infile);
                             exit(1);
                     }
                     log_kitc_redir(inst.num,0, inst.infile);
                     dup2(file_src_in,0);

             }
                     if (inst.outfile != NULL){

                     if (file_src_out <0){
                             log_kitc_file_error(inst.num, inst.outfile);
                             exit(1);
                     }
                     log_kitc_redir(inst.num,1, inst.outfile);
                     dup2(file_src_out,1);

                   }



log_kitc_status_change(inst.num,getpid(),0,array_status[inst.num].cmd_ptr,4);
                    char try1[100];
		    char instruct_command[100];
		    strcpy(instruct_command,array_status[inst.num].array_argv[0]);

                                   strcpy(try1,task_path[0]);
                                   strcat(try1,instruct_command);
                                   execv(try1,array_status[inst.num].array_argv);
				   char try2[100];
				   strcpy(try2,task_path[1]);
				   strcat(try2,instruct_command);
				   execv(try2,array_status[inst.num].array_argv);
				   log_kitc_exec_error(array_status[inst.num].cmd_ptr);
                                   exit(1);



 
                         }else{
				  
				  int pid=-1;
		            	
                              
			    
				    pid = waitpid(-1,&status_exit,0);
			
				exec=0;
		
			   
			if(pid== array_status[inst.num].pid){	  
                              if (  sigstop==0 && sigint==0){
                               int status_exit1 =WEXITSTATUS(status_exit);
                               log_kitc_status_change(inst.num, pid,0,array_status[inst.num].cmd_ptr,0);
                              forground_pid1=-1;
                               array_status[inst.num].status=3;
                               array_status[inst.num].exit_code=status_exit1;
				  }}else	{     if(pid==-1){
						 if (sigstop ==1){
                                          log_kitc_status_change(inst.num,array_status[inst.num].pid ,0,array_status[inst.num].cmd_ptr,3);
                                          sigstop=0;
                                          forground_pid1=-1;
                                          array_status[inst.num].status=2;
                                                }

					 }
				
			   else{	for(int i=1;i<255;i++){
					if(array_status[i].pid==pid){
						kill_tasknum=i;
						kill_pid=pid;
					}
				}
			        array_status[kill_tasknum].exit_code=WEXITSTATUS(status_exit);
                if (kill1== 1){
                  log_kitc_status_change(kill_tasknum,kill_pid,1,kill_cmd,1);
                   array_status[kill_tasknum].status=4;

                    kill1=0;

                }else if(suspend==1){
                         log_kitc_status_change(kill_tasknum,kill_pid,1,kill_cmd,3);
                         array_status[kill_tasknum].status=2;
                         suspend=0; }
                else{
                  array_status[kill_tasknum].status=3;
                log_kitc_status_change(kill_tasknum,kill_pid,1,kill_cmd,0);
                }

	   }
			}}  }else{  if (array_status[inst.num].status==1)
                                                     { log_kitc_status_error(inst.num,1);

                                                        }
						     if(array_status[inst.num].status==2){
                                                                log_kitc_status_error(inst.num,2);

                                                        }



                                             }
                   }}
                

/*purge TASKNUM: removes TASKNUM from the list of tasks. */
              if(strcmp("purge",argument)==0){
		        if (task[inst.num] != NULL && array_status[inst.num].status!=1 && array_status[inst.num].status !=2){
                                num--;
				 for (int m =0;m<(MAXARGS+1);m++){
                    array_status[inst.num].array_argv[m]=NULL;
                }
            array_status[inst.num].pid=-1;
            array_status[inst.num].exit_code=-1;
            array_status[inst.num].status=-1;
            memset(array_status[inst.num].cmd_ptr,'\0', sizeof(array_status[inst.num].cmd_ptr));
	   
                                task[inst.num]=NULL;
                                log_kitc_purge(inst.num);
                        }else{
				if (array_status[inst.num].status ==1){
					log_kitc_status_error(inst.num,1);
				}else if (array_status[inst.num].status ==2){
						 log_kitc_status_error(inst.num,2);
				}else{
                                log_kitc_task_num_error(inst.num);
				}
                        }

	       } 
	       if(strcmp("bg",argument)==0){
		         if (task[inst.num] ==NULL){
                                                log_kitc_task_num_error(inst.num);

                                        }else{
						if (array_status[inst.num].status==0 || array_status[inst.num].status==3 || array_status[inst.num].status==4){
				        int file_src_in=0;
                                        int file_src_out=0;

                                         if (inst.infile !=NULL){
                      file_src_in = open(inst.infile,O_RDONLY);
                      }
                                         if (inst.outfile != NULL){
                       file_src_out = open(inst.outfile,O_WRONLY|O_TRUNC|O_CREAT,0600);



                   }  if (file_src_in>=0 && file_src_out>=0){
                           array_status[inst.num].status=1;


                     }                    kill_tasknum=inst.num;
					  strcpy(array_status[inst.num].type,"bg");
					 strcpy(kill_cmd,array_status[inst.num].cmd_ptr);
	    
					  if (!(array_status[inst.num].pid=kill_pid=fork())){
						  setpgid(0,0);
						  
				         
						  if (inst.infile !=NULL){

                     if (file_src_in <0){
                             log_kitc_file_error(inst.num, inst.infile);
                             exit(1);
                     }
                     log_kitc_redir(inst.num,0, inst.infile);
                     dup2(file_src_in,0);

             }
                     if (inst.outfile != NULL){

                     if (file_src_out <0){
                             log_kitc_file_error(inst.num, inst.outfile);
                             exit(1);
                     }
                     log_kitc_redir(inst.num,1, inst.outfile);
                     dup2(file_src_out,1);

                   }
		     
		     strcpy(script_bg,array_status[inst.num].cmd_ptr);
                    array_status[inst.num].status=1;
                    char try1[100];
                    char instruct_command[100];
                    strcpy(instruct_command,array_status[inst.num].array_argv[0]);

                                   strcpy(try1,task_path[0]);
                                   strcat(try1,instruct_command);
				  
                                   execv(try1,array_status[inst.num].array_argv);
                                   char try2[100];
                                   strcpy(try2,task_path[1]);
                                   strcat(try2,instruct_command);
                                   execv(try2,array_status[inst.num].array_argv);
                                   log_kitc_exec_error(array_status[inst.num].cmd_ptr);
				 
                                   exit(1);




		      }
					  
					  log_kitc_status_change(inst.num,array_status[inst.num].pid,1,array_status[inst.num].cmd_ptr,4);




					}else{
						  if (array_status[inst.num].status==1)
                                                     { log_kitc_status_error(inst.num,1);

                                                        }
						  if(array_status[inst.num].status==2){
                                                                log_kitc_status_error(inst.num,2);

                                                        }

					}

					}
                                        
	     }
//quit command 
            if (strcmp("quit",cmd)==0){
		    log_kitc_quit();
		    exit(0);
		}
	    sigset_t mask,prev;
	    sigemptyset(&mask);
	    sigaddset(&mask,SIGCHLD);
	    sigprocmask(SIG_BLOCK,&mask,&prev);

           int check=0;
           char array[100];
	   char command[100];
	   
	  strcpy(command,inst.instruct);
           
            for (int j=0;j<10;j++){
		    
		  strcpy(array,instructions[j]);
		    if (strcmp(array,command)==0){
		         check++;	  
		   }}

            if(check==0){
                    num++;
                     for(int i=1; i<255;i++){
                             if (task[i] ==NULL){
                                    strcpy(array_status[i].cmd_ptr,cmd);
                                     
                                     parse(cmd, &inst,array_status[i].array_argv); 
                                           
                                          array_status[i].pid=0;
                                        
                                         task[i] = array_status[i].array_argv;
                                          array_status[i].status=0;
					  log_kitc_task_init(i,cmd);
                                     break;
                                     }
                                      
                                   
                             }
                     }
	    sigprocmask(SIG_SETMASK,&prev,NULL);

        }  // end if(!is_whitespace(cmd))

	free(cmd);
	cmd = NULL;
        free_command(&inst, argv);
    }  // end while(1)

    return 0;
}  // end main()

