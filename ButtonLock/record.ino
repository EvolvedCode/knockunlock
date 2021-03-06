void record(){
  if((digitalRead(rButton) == 0 || millis() - start > longest) && recorded){ //If rButton is pressed or the "longest" time limit has been exceeded and the user has recorded at least one full push.
    rcounting = false;
    recording = false; //Stopped recording. Now we're listening and checking.
    rcurrent = maxpush; //We don't want the if below to execute at all.
    #ifdef SERIAL
      Serial.println("Done Recording!");
      for(int i = 0; i < push_cnt; i++){ //Prints the two arrays that specify the knock over serial, so that the user can set them as default in code.
        Serial.println(ref_delta[i]);
      }
      for(int i = 0; i < push_cnt; i++){
        Serial.println(ref_duration[i]);
      }
    #endif
  }

  if(rcurrent < maxpush){
    if(digitalRead(pButton) == 0 && !rcounting){
      start = millis();
      rcounting = true;
    }

    if(digitalRead(pButton) == 1 && rcounting){
      ref_delta[rcurrent] = start - finish; //This finish is the end of the previous push. Essentially we're finding out how far apart the current and the previous push were.
      finish = millis();
      ref_duration[rcurrent] = finish - start; //This finds the Δt or, in other words, the duration of the current push.
      #ifdef SERIAL
        Serial.println(ref_delta[rcurrent]);
        Serial.println(ref_duration[rcurrent]);
      #endif
      rcurrent++;
      push_cnt = rcurrent;
      rcounting = false;
      recorded = true;
    }
  }
}

