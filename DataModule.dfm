object DMod: TDMod
  Height = 480
  Width = 640
  object RESTClient1: TRESTClient
    Accept = 'application/json, text/plain; q=0.9, text/html;q=0.8,'
    AcceptCharset = 'utf-8, *;q=0.8'
    BaseURL = 'https://www.netlogger.org/api'
    Params = <>
    SynchronizedEvents = False
    OnHTTPProtocolError = RESTClient1HTTPProtocolError
    OnValidateCertificate = RESTClient1ValidateCertificate
    OnNeedClientCertificate = RESTClient1NeedClientCertificate
    OnAuthEvent = RESTClient1AuthEvent
    OnSendData = RESTClient1SendData
    OnReceiveData = RESTClient1ReceiveData
    OnReceiveDataEx = RESTClient1ReceiveDataEx
    Left = 40
    Top = 24
  end
  object RESTRequest1: TRESTRequest
    Client = RESTClient1
    Params = <>
    Response = RESTResponse1
    OnBeforeExecute = RESTRequest1BeforeExecute
    OnAfterExecute = RESTRequest1AfterExecute
    SynchronizedEvents = False
    OnHTTPProtocolError = RESTRequest1HTTPProtocolError
    Left = 40
    Top = 87
  end
  object RESTResponse1: TRESTResponse
    ContentType = 'application/pdf'
    Left = 40
    Top = 144
  end
  object XMLDocument1: TXMLDocument
    BeforeOpen = XMLDocument1BeforeOpen
    AfterOpen = XMLDocument1AfterOpen
    BeforeClose = XMLDocument1BeforeClose
    BeforeNodeChange = XMLDocument1BeforeNodeChange
    AfterNodeChange = XMLDocument1AfterNodeChange
    OnAsyncLoad = XMLDocument1AsyncLoad
    Left = 40
    Top = 208
  end
end
