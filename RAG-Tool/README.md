# RAG 

## [View Code](https://github.com/ImTimTong/Projects/tree/main/RAG-Tool)

## Overview
The **Retrieval-Augmented Generation (RAG) Tool** is a Python script to facilitate querying local PDF textbooks using the langchain for QA chaining and the AI21 studio library for semantic text processing.

## Features
- **PDF Loading**: The tool loads a local PDF textbook for querying.
- **Semantic Text Processing**: Uses the AI21 studio library to chunk text semantically.
- **Vector Embeddings**: Generates vector embeddings from the text chunks and stores them in a Chroma vector database.
- **Retrieval-QA**: Utilizes the RetrievalQA chain to feed results from querying the database to llama2 for answering specific questions.
