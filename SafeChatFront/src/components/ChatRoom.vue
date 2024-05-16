<template>
  <div>
    <el-container>

      <!-- <el-header>

      </el-header> -->


      <el-dialog title="登录" :visible.sync="LoginFormVisible" :modal="true" :show-close="false"
        :close-on-click-modal="false" :close-on-press-escape="false">
        <el-form :model="ruleForm" :rules="rules" ref="ruleForm">

          <el-form-item prop="userName">
            <el-input v-model="ruleForm.userName" placeholder="username"></el-input>
          </el-form-item>

          <el-form-item prop="password">
            <el-input type="password" placeholder="password" v-model="ruleForm.password"
              @keyup.enter.native="submitForm('ruleForm')"></el-input>
          </el-form-item>

        </el-form>

        <div slot="footer" class="dialog-footer">
          <el-button @click="submitForm(ruleForm)">登 录</el-button>
        </div>
      </el-dialog>

      <el-main>


        <el-row type="flex" justify="" center>
          <el-col :span="9">
            <div style="height: 500px;">
              <!-- class="textScroll" -->

              <ul>
                <li v-for="message in messageList" :key="message.time">
                  <el-card shadow="hover">
                    <el-row type="flex" justify="start">
                      <h4>
                        [{{ message.user }}] <strong> {{ message.time }}</strong>
                      </h4>
                    </el-row>
                    <el-row type="flex" justify="start">
                      <h1>
                        {{ message.content }}
                      </h1>
                    </el-row>
                  </el-card>
                </li>
              </ul>
            </div>
          </el-col>
        </el-row>
      </el-main>

      <el-footer>
        <el-form :inline="true" :model="MesssageSender" class="demo-form-inline">
          <el-form-item>
            <el-input v-model="MesssageSender.content" placeholder="send something..."></el-input>
          </el-form-item>

          <el-form-item>
            <el-button type="primary" @click="send">Send</el-button>
          </el-form-item>
        </el-form>
        <el-row>
          <el-button type="danger" size="small" plain round @click="Logout">Logout</el-button>
        </el-row>
      </el-footer>

    </el-container>
  </div>
</template>

<script>
import axios from 'axios';

export default {
  name: 'ChatRoom',
  data: function () {
    return {
      LoginFormVisible: true,
      token: "",
      clientPublicKey: -1,
      clientPrivateKey: -1,
      messageList: {},
      MesssageSender: {
        content: ""
      },
      ruleForm: {
        userName: '',
        password: ''
      },
      rules: {
        username: [
          { required: true, message: '请输入用户名', trigger: 'blur' }
        ],
        password: [
          { required: true, message: '请输入密码', trigger: 'blur' }
        ]
      }
    }
  },
  mounted() {
    // this.LoginFormVisible=(this.$store.state.user=="")
    this.LoginFormVisible = (localStorage.getItem("user") == null);
    // console.log(localStorage.getItem("token"))
    if (localStorage.getItem("token") != "") {
      this.getMessageList();
    }
  },
  methods: {
    getMessageList() {
      axios.get('/api/Messages', {
        params: {
          token: localStorage.getItem("token")
          // password: this.ruleForm.password
        }
      }).then((response) => {
        console.log("getMessage")
        console.log(response);
        this.messageList = response.data.messages

      }).catch((error) => {
        console.log(error);
      });
    },
    swapDHkey() {

      this.clientPrivateKey = Math.floor(Math.random() * (this.q)) + 1;
      this.clientPublicKey = Math.pow(this.a, this.clientPrivateKey);

      axios.post('/api/swapDHKey', {
        token: this.token,
        clientPublicKey: this.clientPublicKey
      }).then((response) => {
        console.log("swapDHKey response");
        console.log(response);
        // console.log(response.data.status);
        if (response.data.status === "success") {

          console.log('serverPublicKey' + response.data.serverPublicKey);
          this.sharedKey = Math.pow(response.data.serverPublicKey, this.clientPrivateKey) % this.q;
          console.log('sharedKey' + this.sharedKey);
          this.LoginFormVisible = false;

          this.getMessageList();
        } else {
          alert("登录过期！")
          this.LoginFormVisible = true;
        }
      })
        .catch((error) => {
          console.log(error);
        });

    },
    submitForm(formName) {

      console.log(formName);
      axios.get('/api/login', {
        params: {
          userName: this.ruleForm.userName,
          password: this.ruleForm.password
        }
      }).then((response) => {
        console.log(response);
        console.log(response.data.valid);
        if (response.data.valid === true) {
          console.log('login success');
          this.LoginFormVisible = false;
          this.token = response.data.token;

          // this.$store.state.user = this.ruleForm.userName
          // this.$store.state.token = this.token
          localStorage.setItem("user", this.ruleForm.userName);
          localStorage.setItem("token", this.token);

          // document.cookie='token='
          this.a = response.data.a;
          this.q = response.data.q;
          this.swapDHkey();


        } else {
          alert("账号或密码错误！")
          this.ruleForm.userName = "";
          this.ruleForm.password = "";
        }
      }).catch((error) => {
        console.log(error);
      });

    },
    send() {
      axios.post('/api/sendMessages', {

        token: localStorage.getItem("token"),
        userName: localStorage.getItem("user"),
        content: this.MesssageSender.content

      }).then((response) => {
        console.log("SendMessage")
        console.log(response);
        // this.messageList = response.data.messages

        this.getMessageList()
        this.MesssageSender.content=""

      }).catch((error) => {
        console.log(error);
      });
    },
    Logout() {
      localStorage.removeItem("user")
      localStorage.removeItem("token")
      location.reload()
    }
  }
}
</script>

<style scoped>
.textScroll {
  display: inline-block;
  position: fixed;
  top: 0;
  bottom: 23.2rem;
  overflow: scroll;
  /* right: 0; */
  /* width: 100%; */
  margin-bottom: 4.7rem;
  background-color: rgb(241, 243, 244);
}
</style>