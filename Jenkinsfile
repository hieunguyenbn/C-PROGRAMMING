pipeline {
  agent any
  stages {
    stage('Clean workspace') {
      parallel {
        stage('Clean workspace') {
          steps {
            deleteDir()
          }
        }

        stage('Clone source code') {
          agent any
          steps {
            echo 'Cloning the source code'
          }
        }

        stage('Build the source code') {
          steps {
            sh '''git clone https://github.com/hieunguyenbn/C-PROGRAMMING.git

cd C-PROGRAMMING/Assignment1/HieuNS1_CP_Ass1_CBasic

gcc -I./ assignment1.c -o helloElon'''
          }
        }

        stage('Send email notification') {
          steps {
            mail(subject: 'Build C code', body: 'Elon Build C code', from: 'elon_nguyen', to: 'hieunguyen95bn@gmail.com', replyTo: 'hieunguyen95bn@gmail.com', cc: 'hieunguyenbn.dev@gmail.com')
          }
        }

      }
    }

  }
}