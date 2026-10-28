#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<signal.h>
#include<sys/file.h>

int pid_fd;

/*step 9:signal handler
 * when the daemon receives SIGTERM,this function is called.
 * SIGTERM is used to terminate the daemon.*/

void handle_signal(int sig)
{
        FILE *log;
        log=fopen("/tmp/student_daemon.log","a");

        if(log!=NULL)
        {
                if(sig==SIGTERM)
                {
                        fprintf(log,"SIGTERM received-daemon terminating\n");
                        fclose(log);
                        unlink("/tmp/student_daemon.pid");
                        exit(0);
                }
                  if(sig==SIGHUP)
                {
                       fprintf(log,"SIGHUP received -confirmation reloaded\n");
                }
                    fclose(log);
        }
}
int main()

{
       /*step 1:Get information about the current process */
	
	pid_t pid;
        printf("Before fork\n");
        printf("PID =%d\n",getpid());
        printf("PPID=%d\n",getppid());

        /*step 2:first fork()
         * this is the first step in detaching the process from the terminal.*/

        pid=fork();
        if(pid<0)     //fork failed
        {
                perror("fork");
                exit(EXIT_FAILURE);
        }
        if(pid>0)       //executing in parent;value is child's PID 
        {
                printf("parent process:PID=%d\n",getpid());
                exit(EXIT_SUCCESS);
        }

        printf("child process:PID=%d\n",getpid());

        /*step 3:setsid()-creates a new session if the calling process is eligible.(y we need,doesn't completely detach the process from the terminal/session structure.)
         * after setsid():
         *         -process becomes session leader
         *         -process becomes process-group leader
         *         -process gets detached from controlling terminal*/

        if(setsid() <0)
        {
                perror("setsid");
                exit(0);
        }
        printf("After setsid() \n");
        printf("PID=%d\n",getpid());
        printf("PPID=%d\n",getppid());
        printf("PGID=%d\n",getpgid(0));
        printf("SID=%d\n",getsid(0));

       /*step 4:second fork- the parent of this fork exits.
        * the final child is no longer a session leader.
        * this helps prevent the daemon from acquiring a controlling terminal.*/
         pid=fork();
           if(pid<0)
           {
                   perror("fork");
                   exit(0);
           }

           if(pid>0)
           {
                   exit(EXIT_SUCCESS);
           }

            //Final daemon
           printf("Final daemon:PID=%d\n",getpid());

      /*step 5:umask(0)
      * umask() controls default permissions for newly created files.
   * umask()) clears the file creation mask.it also returns the previous mask.*/
          mode_t old_mask;
          mode_t new_mask;
          old_mask = umask(0);
          new_mask=0;
          printf("old mask=%03o\n",old_mask);
         printf("new mask=%03o\n",new_mask);

       /*step 6:chdir("/")
        * changes the daemon's current working directory to the root directory.
        * this prevents the daemon from keeping the directory from which it was started busy.*/
         if(chdir("/")<0)
         {
                 perror("chdir");
                 exit(0);
         }

         char cwd[100];
         if(getcwd(cwd,sizeof(cwd))==NULL)
         {
                 perror("getcwd");
                 exit(0);
         }
         printf("current working directory=%s\n",cwd);


    /*step 7:redirect standard file descriptors
     * 0->stdin,  1->stdout,  2->stderr
     *dev/null/ is used  so the daemon not depend on the terminal for input/output.*/

         int fd;
         fd=open("/dev/null",O_RDWR);
         if(fd<0)
         {
                 perror("open");
                 exit(0);
         }

         dup2(fd, STDIN_FILENO);
         dup2(fd, STDOUT_FILENO);
          dup2(fd, STDERR_FILENO);

         if(fd>STDERR_FILENO)
         {
                 close(fd);
         }

       /*step 8:Create PID file
        * the daemon's PID is stored in:/tmp/student_daemon.pid
        * this allows us to find the daemon process later.*/

         pid_fd=open("/tmp/student_daemon.pid",O_RDWR|O_CREAT,0666);
         if(pid_fd<0)
         {
                 exit(EXIT_FAILURE);
         }

         if(flock(pid_fd,LOCK_EX|LOCK_NB)<0)
         {
                 close(pid_fd);
                 exit(EXIT_FAILURE);
         }
         if(ftruncate(pid_fd,0)<0)
         {
                 close(pid_fd);
                 exit(EXIT_FAILURE);
         }
         dprintf(pid_fd,"%d\n",getpid());
/*step 9:Register SIGTERM handler
     * when SIGTERM is received:kill _SIGTERM <PID>
     * the handle_signal() function will be called.*/
        signal(SIGTERM,handle_signal);
        signal(SIGHUP,handle_signal);
        while(1)
        {
         /*step 10:Daemon loop and logging.
          * The daemon continuously runs in the background.
          * Every 10 seconds it writes a message to:/tmp/student_daemon.log*/
                FILE *log;
                log=fopen("/tmp/student_daemon.log","a");

                if(log!=NULL)
                {
                        fprintf(log,"Daemon is running\n");
                        fclose(log);
                }
                sleep(10);
        }

        //printf("child PPID before parent exit=%d\n",getppid());
        //sleep(5);
        // printf("child PPID after parent exit=%d\n",getppid());

        return 0;

}
         
  
