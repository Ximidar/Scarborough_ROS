
(cl:in-package :asdf)

(defsystem "scarborough-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "Motor_Speed" :depends-on ("_package_Motor_Speed"))
    (:file "_package_Motor_Speed" :depends-on ("_package"))
    (:file "Desired_Directions" :depends-on ("_package_Desired_Directions"))
    (:file "_package_Desired_Directions" :depends-on ("_package"))
    (:file "YPR" :depends-on ("_package_YPR"))
    (:file "_package_YPR" :depends-on ("_package"))
    (:file "Kill_Switch" :depends-on ("_package_Kill_Switch"))
    (:file "_package_Kill_Switch" :depends-on ("_package"))
  ))