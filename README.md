<h1>1. Philosophers?</h1>
<h2>1) Introduction</h2>

The Dining Philosophers Problem is a classic example in computer science that demonstrates the challenges of concurrent programming and synchronization. It was originally proposed by Dijkstra in 1965 and has since been used to illustrate the complexities of resource sharing and deadlock prevention in various systems. In this problem, a group of philosophers are seated around a circular table, each with a bowl of rice and a pair of chopsticks. The challenge is to enable each philosopher to eat without causing a deadlock or starvation, while using only the available chopsticks.

The Dining Philosophers Problem revolves around the challenge of coordinating the actions of multiple processes or threads that share resources in a mutually exclusive manner. Each philosopher can be in one of three states: eating, thinking, or sleeping. To eat, a philosopher needs to pick up the chopsticks on either side of them. However, the chopsticks can only be used by one philosopher at a time, and they must be put back on the table before the philosopher can start thinking or sleeping again. This creates a potential for deadlock, where all philosophers are waiting for each other to release the chopsticks, and none of them can make progress. In addition, if the system is not properly synchronized, some philosophers may starve and never get a chance to eat. The challenge is to design a solution that avoids both deadlock and starvation, while ensuring that all philosophers get a fair share of the resources.

<p>
  <img src="https://user-images.githubusercontent.com/101046397/231211955-c40d459a-8d33-44ec-9418-7530abbe1e14.png" width="70%">
</p>

<h2>2) Problem</h2>

<p>If it is said that a meal is possible only when the i<sup>th</sup> philosopher obtains chopsticks i, i+1, let's assume that the i<sup>th</sup> philosopher grabs the chopsticks one by one to proceed with the meal, as shown in the code above. In the method of grabbing chopsticks i+1 after grabbing chopsticks i times like this, you can see how every ith philosopher falls into a deadlock because he can't get two chopsticks when he grabs chopsticks i times. Deadlocks are discussed later.</p>
<p>There are 3 ways to solve the above problem:</p>
<ol>
  <li>Keep the number of philosophers less than the number of chopsticks.</li>
  <li>Grasp both chopsticks at the same time when you can use both chopsticks, rather than one chopstick at a time.</li>
  <li>If the ith philosopher has an odd index, he will hold chopstick number i, and if it is an even index, he will hold chopstick number i+1.</li>
</ol>

<h1>1. Thread</h1>
<h2>1) Context Switch</h2>

<p>When a process is scheduled by an operating system, let's assume that the environment in which the operating system operates is a single core. Since only one task can exist in one core, switching between processes such as processing one process and processing the next process is required to process all processes. This kind of conversion of the processed process is called <strong>Context Switch</strong>.</p>
<p>Context switch occurs when the time quantum allocated to the process is exhausted, or when an interrupt such as an I/O call occurs. Since the occurrence of Context Switch means moving from an existing task to a new task, it must be possible to call a new task as well as save the previously performed task so that it can be performed later. This process is in charge of a place called <strong>Dispatcher of Kernel</strong>, and it is done using a data structure called <strong>PCB (Process Control Block)</strong>.</p>
<p><em>Time Quantum</em> means the total amount of time a process can process at one time. In general, the Time Quantum allocated to a process is so small that users cannot perceive it. This makes the user feel as if all processes are being processed at the same time, even though only one process can be processed at a time.</p>

<p>
  <img src="https://user-images.githubusercontent.com/101046397/231221527-ba0a447f-f186-4c81-9ff2-5a22c373295c.png" width="70%">
</p>

<p>Context Switch occurs between processes and is essential to understand because Thread Switch is not much different. The flow for Context Switch is triggered by Interrupt and recorded based on system calls. The data structure called PCB may be different for each operating system but generally includes the contents shown in the figure above. The contents stored in the PCB according to the context switch are the state information of a process. This phenomenon is greatly affected by the structure of the processor. Although the operation consumption of Context Switch may vary depending on the processor, it is not light. Additionally, Context Switch does not occur during a system call, including working on the PCB of Context Switch.</p>
<p>Dispatcher handles the Context Switch and is triggered by Interrupt. Interrupt calling Dispatcher is divided into Preemptive Scheduling and Non-Preemptive Scheduling. The PCB used by each process is located in the memory space used by Kernel. In the case where there are many PCBs and all of them cannot be loaded into the memory, they are processed in the same way as the general process. This can be solved through the Virtual Address and Demanding Page techniques. </p>
<p>CISC processors express the operation as a single instruction, resulting in a relatively small amount of instructions compared to RISC. However, the CPU clock speed is reduced because the instruction is complex. RISC processors express the operation as a combination of instructions, resulting in a fast execution speed but an overhead compared to CISC for context switch. </p>
<p>Context Switch is not a cheap operation, so excessive Context Switch should be avoided. It is important to understand additional terms such as system call and interrupt.</p>

<p>
  <img src="https://user-images.githubusercontent.com/101046397/231222449-2c122c83-05ce-449c-b027-9114358caade.png" width="70%">
</p>
<h2>1) Threads?</h2>
<h3>1. Threads and processes</h3>
<p>If processes were a unit of scheduling by the operating system, their processing unit is actually a thread. All processes have at least one thread called <em>Main Thread</em>, and processes are processed in units of threads.</p>
<p>If you don't understand that a thread is basically the basic unit in which a process is processed, it's okay to understand that one thread is one execution flow. In other words, a thread is an execution flow of a smaller unit than the processes constituting the process.</p>
<p>As for processes, different processes occupy different memory spaces, and they maintain space independence by receiving Protection Domain support from the operating system. On the other hand, in the case of threads constituting a process, since the memory space of each thread is not supported by Protection Domain, each thread can read and write each other's memory space.</p>
<p>One process composed of one thread is controlled once by the operating system and processes work in a single flow. However, if this process is divided into several flows and multiple threads are placed, the work is completed in parallel according to the user's environment. can do.</p>
<p>Therefore, if threads are processed in the process to ensure parallelism well, expensive IPC is not required unlike Cooperative Process, and expensive Context Switch may not be required frequently. In other words, by making a program in which multiple processes collaborate, multiple threads work, it is possible to make the same function at a lower cost than a process. However, since the threads within the process share the same memory space and Protection Domain is not supported, attention must be paid to synchronization.</p>

<h3>1. Number of threads per process</h3>
<p>The number of threads per process is an important factor to consider for proper parallelism and synchronization. But what is the ideal number of threads? It depends on the logical cores that the machine can handle. For instance, if your CPU has 8 cores and 16 threads, you can process 16 threads simultaneously. It is worth noting that this feature is only supported when the kernel supports threading, which is explained in User-Level and Kernel-Level threads. It is important to mention that the 16 threads of the CPU specification are different from the threads processed by the process. These 16 threads from 8 cores and 16 threads of the CPU specification work as logical cores, allowing the machine to perform tasks in parallel. Having too many threads can result in excessive overhead and can reduce the performance of the system. Therefore, it is essential to determine the optimal number of threads for a given task. </p>

<p>
  <img src="https://user-images.githubusercontent.com/101046397/231225633-fa17ae66-3348-44c4-9ec7-46e8dc0b092b.png" width="70%">
</p>

<p>To ensure proper parallelism, it's important to create a suitable number of threads in a process. Simply creating threads according to the number of logical cores may seem like a solution, but it's not always effective. The performance of a computer depends on various hardware components such as the CPU, memory, and disk. If a task requires more device time, such as accessing data from the disk in a server task, the CPU may not be required to process other threads. If there are exactly as many threads as logical cores, the logical core assigned to each thread will remain idle until the device time is complete. Therefore, it's important to consider the device time while creating threads to ensure that each thread is utilized efficiently.</p>

<p>When designing a program, the number of threads needed should depend on whether or not the tasks require device time. If tasks do not require device time, it is appropriate to have as many threads as the number of logical cores available. However, if tasks do require device time, the number of threads should be proportional to the device time. For example, if 1/4 of a program's tasks do not require device time and 3/4 do, then it is appropriate to have three times as many threads as logical cores available for the device time tasks. It is important to note that although higher numbers of threads increase CPU utilization, it does not necessarily increase throughput. This is because Thread Switch between threads is lighter than Context Switch between processes. Threads within the same process share resources such as code and data segments, which makes Thread Switch relatively lighter than Context Switch. Additionally, each thread has a separate Program Counter (PC) because they execute different instructions.</p>

<p>
  <img src="https://user-images.githubusercontent.com/101046397/231227862-919e873e-9d45-42d4-91c2-f0b7d2d0949f.png" width="70%">
</p>


