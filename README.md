# 🍝 42_Philosophers

A multithreaded simulation of the classic "Dining Philosophers Problem" implemented in **C**.  
This project explores synchronization, concurrency, and resource sharing among multiple threads.

---

## 🔧 Features

- 🧠 **Philosophers' Behavior**: Each philosopher alternates between thinking and eating.  
- 🍴 **Fork Management**: Philosophers require two forks to eat; they pick them up and put them down accordingly.  
- ⏱️ **Time Management**: Configurable time to simulate thinking, eating, and sleeping.  
- 🔒 **Mutexes**: Ensures mutual exclusion when accessing shared resources.  
- ⚠️ **Deadlock Prevention**: Implemented strategies to avoid deadlock situations.  
- 💀 **Starvation Avoidance**: Ensures all philosophers get a chance to eat, preventing starvation.

---

## 🛠️ Installation

1. **Clone the repository**:

git clone https://github.com/RaminSanei/42_Philosophers.git

2. **Navigate into the project directory**:

cd 42_Philosophers

3. **Compile the project**:

make

4. **Run the simulation**:

./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]

Example:

./philo 5 800 200 200 7

---

## 📚 Resources

- [The Dining Philosophers Problem - Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [42 Philosophers Project Guide](https://medium.com/@denaelgammal/dining-philosophers-problem-42-project-guide-mandatory-part-a20fb8dc530e)

---

## 📄 License

This project is licensed under the terms of the 42 School's internal license agreement.

