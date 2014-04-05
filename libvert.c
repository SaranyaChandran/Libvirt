#include <stdio.h>
#include <stdlib.h>
#include <libvirt/libvirt.h>

void main()
{

   int i,val=-1,ch,num_domains;
   int *active_domains;
   char dom_name[20];
   virConnectPtr conn;
   virDomainPtr vdp;

   conn = virConnectOpen("xen:///");

   if (conn == NULL) {
       fprintf(stderr, "Error opening connection to XEN:/// \n");
       //return 1;
   }
   else
   {

//For finding Active Devices
       num_domains=virConnectNumOfDomains(conn);
       active_domains=malloc(sizeof(int) * num_domains);
       num_domains = virConnectListDomains(conn, active_domains, num_domains);

       printf("Active domain IDs : \n");
       for (i = 0 ; i < num_domains ; i++) {
           printf(" %d\n", active_domains[i]);
       }
       free(active_domains);

       while(1)
       {
           
           printf("1.Start\n2.Suspend\n3.Resume\n4.Shutdown\n");
           scanf("%d",&ch);

           printf("\n  Insert the Domian Name");
           scanf("%s",dom_name);
 
           vdp=virDomainLookupByName(conn,dom_name);
       
           switch(ch)
           {
               case 1:/* Start */
                      val=virDomainCreate(vdp);
                      if(val==0)
                          printf("Success");
                      else
                          printf("Failed");
                      break;
               case 2:/* Suspend */
                      val=virDomainSuspend(vdp);
                      if(val==0)
                          printf("Success");
                      else
                          printf("Failed");
                      break;
               case 3:/* Resume */
                       val=virDomainResume(vdp);
                       if(val==0)
                           printf("Success");
                       else
                           printf("Failed");
                       break;

               case 4: /* Shutdown */
                       val=virDomainShutdown(vdp);
                       if(val==0)
                           printf("Success");
                       else
                           printf("Failed");
                       break;
               
           }
       }
       virConnectClose(conn);
   }
}
