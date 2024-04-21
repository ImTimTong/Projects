# Tool: RAG
# Author: Timothy Tong
# Description: Loads local PDF textbook for querying llama2. Uses langchain for QA chaining, AI21 studio library to chunk text semantically. 

import os
from getpass import getpass
os.environ["AI21_API_KEY"] = getpass()                                                      # Enter API key for AI21 Studio

from langchain_community.document_loaders import PyPDFLoader
loader = PyPDFLoader("mypdf.pdf")                                                           # Load pdf
pages = loader.load_and_split()                                                             # Split pdf into pages

#Select specific textbook chapter want information from and store the text
text = ""
for page in pages[22:47]: 
    text += page.page_content
    print(page.page_content)                                                                # Double check if correct pages selected

# Use AI21 studio's library to chunk text semantically and then merge to chunk size
from langchain_ai21 import AI21SemanticTextSplitter
semantic_text_splitter_chunks = AI21SemanticTextSplitter(chunk_size=1000)
chunks = semantic_text_splitter.split_text(file_content)

from langchain_chroma import Chroma
from langchain.embeddings import OllamaEmbeddings

from langchain.llms import Ollama
from langchain.chains import RetrievalQA

# Make vector embeddings from the chunks and store into Chroma vector database
oembed = OllamaEmbeddings(base_url="http://localhost:11434", model="nomic-embed-text")
vectorstore = Chroma.from_texts(chunks, oembed)
retriever = vectorstore.as_retriever()

# Make a query 
query = "What is retrieval-augmented generation?"

# Uncomment lines below to perform a similarity search and get related info from DB
# info = vectorstore.similarity_search(query)
# print(info)

# Use RetrievalQA chain to feed results from querying databse to llama2 for answer 
ollama = Ollama(base_url='http://localhost:11434', model="llama2")
qachain=RetrievalQA.from_chain_type(ollama, retriever=vectorstore.as_retriever())
qachain.invoke({"query": query})
