
#include <condition_variable>
#include <cstdio>
#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <sstream>

// Chat Bot Custom Header Class
#include "chatbot.h"

// Socket.IO C++ Client
#include <sio_client.h>

// Set Library Knowledge based.
record KnowledgeBase[] = {
  {"WHAT IS YOUR NAME", // Input
  // Output or Response based on Input.
  {"MY NAME IS CHATTERBOT3.",
   "YOU CAN CALL ME CHATTERBOT3.",
   "WHY DO YOU WANT TO KNOW MY NAME?"}
  },

  {"HI", 
  {"HI THERE!",
   "HOW ARE YOU?",
   "HI!"}
  },
  
  {"HOW ARE YOU",
    {
      "I'M DOING FINE!",
      "I'M DOING WELL AND YOU?"
    }
  },

  {"WHO ARE YOU",
  {"I'M AN A.I PROGRAM.",
   "I THINK THAT YOU KNOW WHO I'M.",
   "WHY ARE YOU ASKING?"}
  },

  {"ARE YOU INTELLIGENT",
  {"YES,OFCORSE.",
   "WHAT DO YOU THINK?",
   "ACTUALY,I'M VERY INTELLIENT!"}
  },

  {"HELLO",
    {
      "HELLO"
    }
  },

  {"ARE YOU REAL",
  {"DOES THAT QUESTION REALLY MATERS TO YOU?",
   "WHAT DO YOU MEAN BY THAT?",
   "I'M AS REAL AS I CAN BE."}
  }
};

class SampleClient {
  public:
    SampleClient() {
      // Input Knowledge Base On ChatBot Class.
      ChatBot.setKnowledge(KnowledgeBase);
      
      // Input Size of array struct of Knowledge Base.
      int sizeofknowledge =  sizeof(KnowledgeBase)/sizeof(*KnowledgeBase);
      ChatBot.setSizeOfKnowledge(sizeofknowledge);
    }

    // Calling Socket IO Client
    sio::client client;
    sio::socket::ptr socket;

    
    std::mutex sio_mutex;
    std::condition_variable_any sio_cond;

    // Add Queue for handling receiver from node js.
    std::queue<sio::message::ptr> sio_queue;
    
    bool is_connected = false;

    
    void on_close() {
      std::cout << "Connection Close." << std::endl;
      exit(EXIT_FAILURE);
    }

    void on_fail() {
      std::cout << "Connection Failed." << std::endl;
      exit(EXIT_FAILURE);
    }

    
    void on_open() {
      std::cout << "Connection Open." << std::endl;
      std::unique_lock<std::mutex> lock(sio_mutex);
      is_connected = true;
      sio_cond.notify_all();
    }

    void on_run(sio::event& e) {
      std::unique_lock<std::mutex> lock(sio_mutex);
      sio_queue.push(e.get_message());
      sio_cond.notify_all();
    }

    void run(const std::string& url, const std::string& name) {
      // Set Close, Fail, and Open Listener
      client.set_close_listener(std::bind(&SampleClient::on_close, this));
      client.set_fail_listener(std::bind(&SampleClient::on_fail, this));
      client.set_open_listener(std::bind(&SampleClient::on_open, this));
      
      // Connect Client Socket IO
      client.connect(url);
      { 
        std::unique_lock<std::mutex> lock(sio_mutex);
        if (!is_connected) {
  	       sio_cond.wait(sio_mutex);
        }
      }
      
      socket = client.socket();
      socket->on("run", std::bind(&SampleClient::on_run, this, std::placeholders::_1));
      {
        sio::message::ptr send_data(sio::object_message::create());
        std::map<std::string, sio::message::ptr>& map = send_data->get_map();
    
        map.insert(std::make_pair("type", sio::string_message::create("native")));
        map.insert(std::make_pair("name", sio::string_message::create(name)));

        socket->emit("join", send_data);
      }

      while(true) {
       
        std::unique_lock<std::mutex> lock(sio_mutex);
        while (sio_queue.empty()) {
  	       sio_cond.wait(lock);
        }

        // Receive Message From Queue Handler
        sio::message::ptr recv_data(sio_queue.front());
        std::stringstream output;
        char buf[1024];
        
        FILE* fp = nullptr;

        std::string command = recv_data->get_map().at("command")->get_string();

        // Send to ChatBot Class the Message.
        ChatBot.setResponse(command);
        
        sio::message::ptr reply_data(sio::object_message::create());
        std::map<std::string, sio::message::ptr>& map = reply_data->get_map();
        map.insert(std::make_pair("output", sio::string_message::create(ChatBot.getResponse())));
        std::cout << output.str();

        socket->emit("reply", reply_data);
        
        sio_queue.pop();
      }
    }

  private:
    chatbot ChatBot; // Create Class for Chat Bot.
};

int main(int argc, char* argv[]) { 
  if (argc != 3) {
    std::cerr << "You must have 3 arguments." << std::endl;
    exit(EXIT_FAILURE);
  }

  SampleClient client;
  client.run(argv[1], argv[2]);

  return EXIT_SUCCESS;
}
