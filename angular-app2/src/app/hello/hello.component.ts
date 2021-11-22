import { Component, OnInit} from '@angular/core';

@Component({
  selector: 'app-hello2',
  styleUrls: ['./hello.component.css'],
  templateUrl:'./hello.component.html'
})

export class HelloComponent implements OnInit {
  title:string | undefined;
  message:string| undefined;
  count: number =0;

  constructor() {}

  ngOnInit(){
    this.title = 'Hello-app2';
    this.message = 'ボタンをクリック!';
    this.count = 0;
  }

  doClick(){
    this.message = ++this.count + "回、クリックしました。";
  }
}
