# Parallax

Parallax is a lightweight, command-line-driven task management tool designed for simplicity and efficiency. It allows users to quickly manage tasks, notes, and projects directly from their terminal.

---

## Core Features

* **Task Management (CRUD):** Full Create, Read, Update, and Delete functionality for all your tasks.
* **Detailed Tasks:**
    * Start with simple **descriptors** for quick entry.
    * Future support for task **classes/categories**.
    * A **centralized note structure** (e.g., file-based database) to keep all task-related information in one place.
* **User Commands:**
    * Quickly **create** new tasks (e.g., `parallax -c "New Task"`).
    * Control **verbosity** for detailed or summary views.
    * **List** all or filtered tasks.
* **Fuzzy Finder:**
    * Efficiently search for tasks even with partial or misspelled queries.
    * **Ranks** search results by similarity to find what you're looking for faster.

---

## Development Roadmap

Here is the planned development path for Parallax:

1.  **User Commands:** Implement the core command-line entry point and argument parsing.
2.  **Task Structure:** Design and implement the underlying data structure for tasks.
3.  **File Handling:** Build the system for storing, reading, and updating tasks on disk.
4.  **Fuzzy Finder:** Integrate a fuzzy search algorithm for intuitive task retrieval.
5.  **Server Sync (Future):** Implement functionality to sync tasks with a remote server.
