import { Component, OnInit } from '@angular/core';
import { FormBuilder, FormGroup} from '@angular/forms';

@Component({
  selector: 'app-hello',
  templateUrl: './hello.component.html',
  styleUrls: ['./hello.component.css']
})
export class HelloComponent implements OnInit {
  title:string | undefined;
  message:string | undefined;
  myControl: FormGroup = new FormGroup({});

  constructor(private fb: FormBuilder) {}

  ngOnInit(): void {
    this.title = 'Hello-app3';
    this.message = 'FormBuilderを使う';
    this.myControl = this.fb.group({
      name:[''],
      mail:[''],
      age:[0]
    });
  }

  onSubmit(){
    let result = this.myControl.value;
    this.message = JSON.stringify(result);
  }
}
