# encoding:utf-8


import sys

sys.path.append('../..')

import struct

from autonavi.decoder import etatrafficupdate
from utils import httpwrapper
from utils import zipwrapper
from xml.dom import minidom


print '\n\33[1m%s\33[0m\n'%("更换数据后要重新构造ETA请求")


tr_address = "10.218.252.21"
tr_port = 8080

cbr_address = "10.218.252.24"
cbr_port = 7196

amap_address = "10.218.252.24"
amap_port = 7197

address = cbr_address
port = cbr_port


chengguang_address = "100.81.153.90"
chengguang_port = 8888
address=chengguang_address
port=chengguang_port

'''
with_mock_address = "100.81.183.87"
with_mock_port = 8765
amap_address = with_mock_address
amap_port = with_mock_port
'''
'''
liantiao_address = 'route.amap.test'
liantiao_port = '8765'
amap_address = liantiao_address
amap_port = liantiao_port
'''
'''
stable_address = '10.218.252.24'
stable_port = 8765
amap_address = stable_address
amap_port = stable_port
'''


def send_request(request):
    # 压缩请求
    request = '1' + struct.pack("I", len(request)) + zipwrapper.gzip_compress(request)

    '''
    with open('request', 'w') as f:
        if f:
            f.write(request)
            f.flush()
            f.close()
    '''

    #print 'address:', address
    #print 'port   :', port

    status, resp = httpwrapper.post(request, address, port, 'etatrafficupdate')

    if status != 200:
        print "\nxlongsrv http status code:", status
    else:
        if resp:
            decoder = etatrafficupdate.ETADecoder12()
            result = decoder.decode(resp)
            print '\n解析结果         :', result
            print '本地错误码       :', decoder.m_cli_err_code
            print '远程错误码       :', decoder.m_srv_err_code
            print '报文总长度       :', decoder.m_package_len
            print '\nETA部分长度      :', decoder.m_eta_len
            print '路径条数         :', decoder.get_path_num()
            for i in range(0, decoder.get_path_num()):
                path = decoder.get_path(i)
                print '路径 ', i, ' 事件数量:', path.get_incident_num()
                print '路径 ', i, ' 道路数量:', path.get_link_num()
            print '\nTR请求结果       :', decoder.m_state
            print '播报内容长度     :', decoder.m_broadcast_len
            if decoder.m_state == 0 and decoder.m_broadcast_len > 0:
                pass  # print zipwrapper.gzip_decompress(decoder.m_broadcast_content)
        else:
            print 'content is null'


def run():

    data_version = 55120

    post_login = ''
    uri_login = 'RouteStatusService/Handle.do?cmdtype=logon&usercode=AN_Amap_IOS_FC&userbatch=0&deviceid=21643_pc&ver=8.0.7.9.1.2.20160831&tosCharset=UTF8'

    status, resp = httpwrapper.post(post_login, tr_address, tr_port, uri_login)

    if status != 200:
        print "\ntraffic repoter http status code:", status
    else:
        login_result = zipwrapper.gzip_decompress(resp)
        print '\n登录结果：', login_result
        doc = minidom.parseString(login_result)
        root = doc.documentElement
        pincode = root.getElementsByTagName("pincode")[0].childNodes[0].data.encode('utf-8')
        print 'pincode:', pincode

    print '\n\33[1m%s\33[0m\n'%('没有ETAInfo')
    request = '<etatrafficupdate Plate="京dfsff9" ContentOptions="0x3C" EtaOptions="1" Type="0x00" Flag="0x80000028" Vers="1.2" DataVers="'+ str(data_version) + '"><vehicle type="0" height="2.6" load="108.9"/><path RerouteMethod="Auto"><startpoint><x>116.405090</x><y>39.988304</y></startpoint><endpoint><x>116.445755</x><y>39.832334</y></endpoint><linklens startlen="1" endlen="2"/><roadlinks IDType="0"><ID>2156659933</ID><ID>2156659879</ID><ID>2156659872</ID><ID>2156659858</ID><ID>2156659754</ID><ID>2156659767</ID><ID>2156659796</ID><ID>2156658776</ID><ID>2156658772</ID><ID>2156658797</ID><ID>2156658657</ID><ID>2156656599</ID><ID>2156656580</ID><ID>2156655706</ID><ID>2156655710</ID><ID>2156655723</ID><ID>2156655686</ID><ID>2156655683</ID><ID>2156655646</ID><ID>2156655629</ID><ID>2156655561</ID><ID>2156655591</ID><ID>2156655574</ID><ID>2156655567</ID><ID>2156655568</ID><ID>2156655196</ID><ID>2156655432</ID><ID>2156655299</ID><ID>2156649678</ID><ID>2156520567</ID><ID>2156520594</ID><ID>2156520589</ID><ID>2156520605</ID><ID>2156520620</ID><ID>2156520707</ID><ID>2156520688</ID><ID>2156520756</ID><ID>2156520773</ID><ID>2156520759</ID><ID>2156520909</ID><ID>2156520852</ID><ID>2156520826</ID><ID>2156520828</ID><ID>2156521832</ID><ID>2156521822</ID><ID>2156521798</ID><ID>2156521738</ID><ID>2156522149</ID><ID>2156522164</ID><ID>2156522172</ID><ID>2156522179</ID><ID>2156522187</ID><ID>2156522224</ID><ID>2156522230</ID><ID>2156518311</ID><ID>2156518300</ID><ID>2156518298</ID><ID>2156518213</ID><ID>2156517984</ID><ID>2156517973</ID><ID>2156517970</ID><ID>2156517958</ID><ID>2156517894</ID><ID>2156517888</ID><ID>2156517885</ID><ID>2156517882</ID><ID>2156517254</ID><ID>2156517200</ID><ID>2156517022</ID><ID>2156517014</ID><ID>2156516984</ID><ID>2156531172</ID><ID>2156531342</ID><ID>2156531351</ID><ID>2156531384</ID><ID>2156531456</ID><ID>2156534927</ID><ID>2156534932</ID><ID>2156534941</ID><ID>2156534944</ID><ID>2156534965</ID><ID>2156535172</ID><ID>2156535200</ID><ID>2156535317</ID><ID>2156535338</ID><ID>2156535340</ID><ID>2156535349</ID><ID>2156535400</ID><ID>2156535407</ID><ID>2156535413</ID><ID>2156535421</ID><ID>2156535427</ID><ID>2156535435</ID><ID>2156539534</ID><ID>2156539541</ID><ID>2156539577</ID><ID>2156539633</ID><ID>2156539638</ID><ID>2156539652</ID><ID>2156539645</ID><ID>2156539871</ID><ID>2156539877</ID><ID>2156469657</ID><ID>2156469681</ID><ID>2156470170</ID><ID>2156470210</ID><ID>2156470217</ID><ID>2156470118</ID><ID>2156470261</ID><ID>2156470278</ID><ID>2156470321</ID><ID>2156470388</ID><ID>2156470438</ID><ID>2156470463</ID><ID>2156470455</ID><ID>2156470475</ID><ID>2156470488</ID><ID>2156465612</ID><ID>2156465107</ID><ID>2156465040</ID><ID>2156465032</ID><ID>2156465011</ID><ID>2156465002</ID><ID>2156464904</ID><ID>2156476142</ID><ID>2156476134</ID><ID>2156476121</ID><ID>2156476124</ID><ID>2156475988</ID></roadlinks></path></etatrafficupdate>'
    send_request(request)

    print '\n\33[1m%s\33[0m\n'%('ETAFlag = 0 路况')
    request = '<etatrafficupdate Plate="京dfsff9" ContentOptions="0x3C" EtaOptions="1" Type="0x00" Flag="0x80000028" Vers="1.2" DataVers="'+ str(data_version) + '"><vehicle type="0" height="2.6" load="108.9"/><path RerouteMethod="Auto"><startpoint><x>116.405090</x><y>39.988304</y></startpoint><endpoint><x>116.445755</x><y>39.832334</y></endpoint><linklens startlen="1" endlen="2"/><roadlinks IDType="0"><ID>2156659933</ID><ID>2156659879</ID><ID>2156659872</ID><ID>2156659858</ID><ID>2156659754</ID><ID>2156659767</ID><ID>2156659796</ID><ID>2156658776</ID><ID>2156658772</ID><ID>2156658797</ID><ID>2156658657</ID><ID>2156656599</ID><ID>2156656580</ID><ID>2156655706</ID><ID>2156655710</ID><ID>2156655723</ID><ID>2156655686</ID><ID>2156655683</ID><ID>2156655646</ID><ID>2156655629</ID><ID>2156655561</ID><ID>2156655591</ID><ID>2156655574</ID><ID>2156655567</ID><ID>2156655568</ID><ID>2156655196</ID><ID>2156655432</ID><ID>2156655299</ID><ID>2156649678</ID><ID>2156520567</ID><ID>2156520594</ID><ID>2156520589</ID><ID>2156520605</ID><ID>2156520620</ID><ID>2156520707</ID><ID>2156520688</ID><ID>2156520756</ID><ID>2156520773</ID><ID>2156520759</ID><ID>2156520909</ID><ID>2156520852</ID><ID>2156520826</ID><ID>2156520828</ID><ID>2156521832</ID><ID>2156521822</ID><ID>2156521798</ID><ID>2156521738</ID><ID>2156522149</ID><ID>2156522164</ID><ID>2156522172</ID><ID>2156522179</ID><ID>2156522187</ID><ID>2156522224</ID><ID>2156522230</ID><ID>2156518311</ID><ID>2156518300</ID><ID>2156518298</ID><ID>2156518213</ID><ID>2156517984</ID><ID>2156517973</ID><ID>2156517970</ID><ID>2156517958</ID><ID>2156517894</ID><ID>2156517888</ID><ID>2156517885</ID><ID>2156517882</ID><ID>2156517254</ID><ID>2156517200</ID><ID>2156517022</ID><ID>2156517014</ID><ID>2156516984</ID><ID>2156531172</ID><ID>2156531342</ID><ID>2156531351</ID><ID>2156531384</ID><ID>2156531456</ID><ID>2156534927</ID><ID>2156534932</ID><ID>2156534941</ID><ID>2156534944</ID><ID>2156534965</ID><ID>2156535172</ID><ID>2156535200</ID><ID>2156535317</ID><ID>2156535338</ID><ID>2156535340</ID><ID>2156535349</ID><ID>2156535400</ID><ID>2156535407</ID><ID>2156535413</ID><ID>2156535421</ID><ID>2156535427</ID><ID>2156535435</ID><ID>2156539534</ID><ID>2156539541</ID><ID>2156539577</ID><ID>2156539633</ID><ID>2156539638</ID><ID>2156539652</ID><ID>2156539645</ID><ID>2156539871</ID><ID>2156539877</ID><ID>2156469657</ID><ID>2156469681</ID><ID>2156470170</ID><ID>2156470210</ID><ID>2156470217</ID><ID>2156470118</ID><ID>2156470261</ID><ID>2156470278</ID><ID>2156470321</ID><ID>2156470388</ID><ID>2156470438</ID><ID>2156470463</ID><ID>2156470455</ID><ID>2156470475</ID><ID>2156470488</ID><ID>2156465612</ID><ID>2156465107</ID><ID>2156465040</ID><ID>2156465032</ID><ID>2156465011</ID><ID>2156465002</ID><ID>2156464904</ID><ID>2156476142</ID><ID>2156476134</ID><ID>2156476121</ID><ID>2156476124</ID><ID>2156475988</ID></roadlinks></path><ETAInfo><ETAFlag>0</ETAFlag><TRRequestData>cmdtype=trafficinfo&pincode=' + pincode + '&datatype=1&gpsdata=AOAVlwACADQI%2BnLqQX4LR7CBMgLcQmYGZ6JeVnn%2B%2F0sUAAA%2BA9H8%2B1gAShQAADEGGfr2SgBIFAAApwi89%2FFBAEQUAADICnz17D8AQhQAAA8NQvPnRAA%2BFAAA%2FA9u8OFFADwUAABZEhju3EIANxQAAKcU5uvXQwA7FAAAEheJ6dJHADsUAACdGQLnzUsAORQAAF8cUeTIUgBEFAAANx9a4cNQAEgUAAAAAA%3D%3D&compress=0&flag=1115422&offset=1&tosCharset=UTF8</TRRequestData></ETAInfo></etatrafficupdate>'
    send_request(request)

    print '\n\33[1m%s\33[0m\n'%("ETAFlag = 1 轨迹点")
    request = '<etatrafficupdate Plate="京dfsff9" ContentOptions="0x3C" EtaOptions="1" Type="0x00" Flag="0x80000028" Vers="1.2" DataVers="'+ str(data_version) + '"><vehicle type="0" height="2.6" load="108.9"/><path RerouteMethod="Auto"><startpoint><x>116.405090</x><y>39.988304</y></startpoint><endpoint><x>116.445755</x><y>39.832334</y></endpoint><linklens startlen="1" endlen="2"/><roadlinks IDType="0"><ID>2156659933</ID><ID>2156659879</ID><ID>2156659872</ID><ID>2156659858</ID><ID>2156659754</ID><ID>2156659767</ID><ID>2156659796</ID><ID>2156658776</ID><ID>2156658772</ID><ID>2156658797</ID><ID>2156658657</ID><ID>2156656599</ID><ID>2156656580</ID><ID>2156655706</ID><ID>2156655710</ID><ID>2156655723</ID><ID>2156655686</ID><ID>2156655683</ID><ID>2156655646</ID><ID>2156655629</ID><ID>2156655561</ID><ID>2156655591</ID><ID>2156655574</ID><ID>2156655567</ID><ID>2156655568</ID><ID>2156655196</ID><ID>2156655432</ID><ID>2156655299</ID><ID>2156649678</ID><ID>2156520567</ID><ID>2156520594</ID><ID>2156520589</ID><ID>2156520605</ID><ID>2156520620</ID><ID>2156520707</ID><ID>2156520688</ID><ID>2156520756</ID><ID>2156520773</ID><ID>2156520759</ID><ID>2156520909</ID><ID>2156520852</ID><ID>2156520826</ID><ID>2156520828</ID><ID>2156521832</ID><ID>2156521822</ID><ID>2156521798</ID><ID>2156521738</ID><ID>2156522149</ID><ID>2156522164</ID><ID>2156522172</ID><ID>2156522179</ID><ID>2156522187</ID><ID>2156522224</ID><ID>2156522230</ID><ID>2156518311</ID><ID>2156518300</ID><ID>2156518298</ID><ID>2156518213</ID><ID>2156517984</ID><ID>2156517973</ID><ID>2156517970</ID><ID>2156517958</ID><ID>2156517894</ID><ID>2156517888</ID><ID>2156517885</ID><ID>2156517882</ID><ID>2156517254</ID><ID>2156517200</ID><ID>2156517022</ID><ID>2156517014</ID><ID>2156516984</ID><ID>2156531172</ID><ID>2156531342</ID><ID>2156531351</ID><ID>2156531384</ID><ID>2156531456</ID><ID>2156534927</ID><ID>2156534932</ID><ID>2156534941</ID><ID>2156534944</ID><ID>2156534965</ID><ID>2156535172</ID><ID>2156535200</ID><ID>2156535317</ID><ID>2156535338</ID><ID>2156535340</ID><ID>2156535349</ID><ID>2156535400</ID><ID>2156535407</ID><ID>2156535413</ID><ID>2156535421</ID><ID>2156535427</ID><ID>2156535435</ID><ID>2156539534</ID><ID>2156539541</ID><ID>2156539577</ID><ID>2156539633</ID><ID>2156539638</ID><ID>2156539652</ID><ID>2156539645</ID><ID>2156539871</ID><ID>2156539877</ID><ID>2156469657</ID><ID>2156469681</ID><ID>2156470170</ID><ID>2156470210</ID><ID>2156470217</ID><ID>2156470118</ID><ID>2156470261</ID><ID>2156470278</ID><ID>2156470321</ID><ID>2156470388</ID><ID>2156470438</ID><ID>2156470463</ID><ID>2156470455</ID><ID>2156470475</ID><ID>2156470488</ID><ID>2156465612</ID><ID>2156465107</ID><ID>2156465040</ID><ID>2156465032</ID><ID>2156465011</ID><ID>2156465002</ID><ID>2156464904</ID><ID>2156476142</ID><ID>2156476134</ID><ID>2156476121</ID><ID>2156476124</ID><ID>2156475988</ID></roadlinks></path><ETAInfo><ETAFlag>1</ETAFlag><TRRequestData>cmdtype=trafficinfo&pincode=' + pincode + '&datatype=1&datatype=1&gpsdata=AOAVlwACADQI%2BnLqQX4LR7CBMgLcQmYGZ6JeVnn%2B%2F0sUAAA%2BA9H8%2B1gAShQAADEGGfr2SgBIFAAApwi89%2FFBAEQUAADICnz17D8AQhQAAA8NQvPnRAA%2BFAAA%2FA9u8OFFADwUAABZEhju3EIANxQAAKcU5uvXQwA7FAAAEheJ6dJHADsUAACdGQLnzUsAORQAAF8cUeTIUgBEFAAANx9a4cNQAEgUAAAAAA%3D%3D&compress=0&flag=1115423&offset=1&tosCharset=UTF8</TRRequestData></ETAInfo></etatrafficupdate>'
    send_request(request)

    print '\n\33[1m%s\33[0m\n' % ("ETAFlag = 2 路况 播报 轨迹点")
    request = '<etatrafficupdate Plate="京dfsff9" ContentOptions="0x3C" EtaOptions="1" Type="0x00" Flag="0x80000028" Vers="1.2" DataVers="'+ str(data_version) + '"><vehicle type="0" height="2.6" load="108.9"/><path RerouteMethod="Auto"><startpoint><x>116.405090</x><y>39.988304</y></startpoint><endpoint><x>116.445755</x><y>39.832334</y></endpoint><linklens startlen="1" endlen="2"/><roadlinks IDType="0"><ID>2156659933</ID><ID>2156659879</ID><ID>2156659872</ID><ID>2156659858</ID><ID>2156659754</ID><ID>2156659767</ID><ID>2156659796</ID><ID>2156658776</ID><ID>2156658772</ID><ID>2156658797</ID><ID>2156658657</ID><ID>2156656599</ID><ID>2156656580</ID><ID>2156655706</ID><ID>2156655710</ID><ID>2156655723</ID><ID>2156655686</ID><ID>2156655683</ID><ID>2156655646</ID><ID>2156655629</ID><ID>2156655561</ID><ID>2156655591</ID><ID>2156655574</ID><ID>2156655567</ID><ID>2156655568</ID><ID>2156655196</ID><ID>2156655432</ID><ID>2156655299</ID><ID>2156649678</ID><ID>2156520567</ID><ID>2156520594</ID><ID>2156520589</ID><ID>2156520605</ID><ID>2156520620</ID><ID>2156520707</ID><ID>2156520688</ID><ID>2156520756</ID><ID>2156520773</ID><ID>2156520759</ID><ID>2156520909</ID><ID>2156520852</ID><ID>2156520826</ID><ID>2156520828</ID><ID>2156521832</ID><ID>2156521822</ID><ID>2156521798</ID><ID>2156521738</ID><ID>2156522149</ID><ID>2156522164</ID><ID>2156522172</ID><ID>2156522179</ID><ID>2156522187</ID><ID>2156522224</ID><ID>2156522230</ID><ID>2156518311</ID><ID>2156518300</ID><ID>2156518298</ID><ID>2156518213</ID><ID>2156517984</ID><ID>2156517973</ID><ID>2156517970</ID><ID>2156517958</ID><ID>2156517894</ID><ID>2156517888</ID><ID>2156517885</ID><ID>2156517882</ID><ID>2156517254</ID><ID>2156517200</ID><ID>2156517022</ID><ID>2156517014</ID><ID>2156516984</ID><ID>2156531172</ID><ID>2156531342</ID><ID>2156531351</ID><ID>2156531384</ID><ID>2156531456</ID><ID>2156534927</ID><ID>2156534932</ID><ID>2156534941</ID><ID>2156534944</ID><ID>2156534965</ID><ID>2156535172</ID><ID>2156535200</ID><ID>2156535317</ID><ID>2156535338</ID><ID>2156535340</ID><ID>2156535349</ID><ID>2156535400</ID><ID>2156535407</ID><ID>2156535413</ID><ID>2156535421</ID><ID>2156535427</ID><ID>2156535435</ID><ID>2156539534</ID><ID>2156539541</ID><ID>2156539577</ID><ID>2156539633</ID><ID>2156539638</ID><ID>2156539652</ID><ID>2156539645</ID><ID>2156539871</ID><ID>2156539877</ID><ID>2156469657</ID><ID>2156469681</ID><ID>2156470170</ID><ID>2156470210</ID><ID>2156470217</ID><ID>2156470118</ID><ID>2156470261</ID><ID>2156470278</ID><ID>2156470321</ID><ID>2156470388</ID><ID>2156470438</ID><ID>2156470463</ID><ID>2156470455</ID><ID>2156470475</ID><ID>2156470488</ID><ID>2156465612</ID><ID>2156465107</ID><ID>2156465040</ID><ID>2156465032</ID><ID>2156465011</ID><ID>2156465002</ID><ID>2156464904</ID><ID>2156476142</ID><ID>2156476134</ID><ID>2156476121</ID><ID>2156476124</ID><ID>2156475988</ID></roadlinks></path><ETAInfo><ETAFlag>2</ETAFlag><TRRequestData>cmdtype=trafficinfo&pincode=' + pincode + '&datatype=1&gpsdata=AOAVlwACADQI%2BnLqQX4LR7CBMgLcQmYGZ6JeVnn%2B%2F0sUAAA%2BA9H8%2B1gAShQAADEGGfr2SgBIFAAApwi89%2FFBAEQUAADICnz17D8AQhQAAA8NQvPnRAA%2BFAAA%2FA9u8OFFADwUAABZEhju3EIANxQAAKcU5uvXQwA7FAAAEheJ6dJHADsUAACdGQLnzUsAORQAAF8cUeTIUgBEFAAANx9a4cNQAEgUAAAAAA%3D%3D&compress=0&flag=1115422&offset=1&tosCharset=UTF8</TRRequestData></ETAInfo></etatrafficupdate>'
    send_request(request)

    print '\n\33[1m%s\33[0m\n' % ("ETAFlag = 3 播报 轨迹点")
    request = '<etatrafficupdate Plate="京dfsff9" ContentOptions="0x3C" EtaOptions="1" Type="0x00" Flag="0x80000028" Vers="1.2" DataVers="'+ str(data_version) + '"><vehicle type="0" height="2.6" load="108.9"/><path RerouteMethod="Auto"><startpoint><x>116.405090</x><y>39.988304</y></startpoint><endpoint><x>116.445755</x><y>39.832334</y></endpoint><linklens startlen="1" endlen="2"/><roadlinks IDType="0"><ID>2156659933</ID><ID>2156659879</ID><ID>2156659872</ID><ID>2156659858</ID><ID>2156659754</ID><ID>2156659767</ID><ID>2156659796</ID><ID>2156658776</ID><ID>2156658772</ID><ID>2156658797</ID><ID>2156658657</ID><ID>2156656599</ID><ID>2156656580</ID><ID>2156655706</ID><ID>2156655710</ID><ID>2156655723</ID><ID>2156655686</ID><ID>2156655683</ID><ID>2156655646</ID><ID>2156655629</ID><ID>2156655561</ID><ID>2156655591</ID><ID>2156655574</ID><ID>2156655567</ID><ID>2156655568</ID><ID>2156655196</ID><ID>2156655432</ID><ID>2156655299</ID><ID>2156649678</ID><ID>2156520567</ID><ID>2156520594</ID><ID>2156520589</ID><ID>2156520605</ID><ID>2156520620</ID><ID>2156520707</ID><ID>2156520688</ID><ID>2156520756</ID><ID>2156520773</ID><ID>2156520759</ID><ID>2156520909</ID><ID>2156520852</ID><ID>2156520826</ID><ID>2156520828</ID><ID>2156521832</ID><ID>2156521822</ID><ID>2156521798</ID><ID>2156521738</ID><ID>2156522149</ID><ID>2156522164</ID><ID>2156522172</ID><ID>2156522179</ID><ID>2156522187</ID><ID>2156522224</ID><ID>2156522230</ID><ID>2156518311</ID><ID>2156518300</ID><ID>2156518298</ID><ID>2156518213</ID><ID>2156517984</ID><ID>2156517973</ID><ID>2156517970</ID><ID>2156517958</ID><ID>2156517894</ID><ID>2156517888</ID><ID>2156517885</ID><ID>2156517882</ID><ID>2156517254</ID><ID>2156517200</ID><ID>2156517022</ID><ID>2156517014</ID><ID>2156516984</ID><ID>2156531172</ID><ID>2156531342</ID><ID>2156531351</ID><ID>2156531384</ID><ID>2156531456</ID><ID>2156534927</ID><ID>2156534932</ID><ID>2156534941</ID><ID>2156534944</ID><ID>2156534965</ID><ID>2156535172</ID><ID>2156535200</ID><ID>2156535317</ID><ID>2156535338</ID><ID>2156535340</ID><ID>2156535349</ID><ID>2156535400</ID><ID>2156535407</ID><ID>2156535413</ID><ID>2156535421</ID><ID>2156535427</ID><ID>2156535435</ID><ID>2156539534</ID><ID>2156539541</ID><ID>2156539577</ID><ID>2156539633</ID><ID>2156539638</ID><ID>2156539652</ID><ID>2156539645</ID><ID>2156539871</ID><ID>2156539877</ID><ID>2156469657</ID><ID>2156469681</ID><ID>2156470170</ID><ID>2156470210</ID><ID>2156470217</ID><ID>2156470118</ID><ID>2156470261</ID><ID>2156470278</ID><ID>2156470321</ID><ID>2156470388</ID><ID>2156470438</ID><ID>2156470463</ID><ID>2156470455</ID><ID>2156470475</ID><ID>2156470488</ID><ID>2156465612</ID><ID>2156465107</ID><ID>2156465040</ID><ID>2156465032</ID><ID>2156465011</ID><ID>2156465002</ID><ID>2156464904</ID><ID>2156476142</ID><ID>2156476134</ID><ID>2156476121</ID><ID>2156476124</ID><ID>2156475988</ID></roadlinks></path><ETAInfo><ETAFlag>3</ETAFlag><TRRequestData>cmdtype=trafficinfo&pincode=' + pincode + '&datatype=1&gpsdata=AOAVlwACADQI%2BnLqQX4LR7CBMgLcQmYGZ6JeVnn%2B%2F0sUAAA%2BA9H8%2B1gAShQAADEGGfr2SgBIFAAApwi89%2FFBAEQUAADICnz17D8AQhQAAA8NQvPnRAA%2BFAAA%2FA9u8OFFADwUAABZEhju3EIANxQAAKcU5uvXQwA7FAAAEheJ6dJHADsUAACdGQLnzUsAORQAAF8cUeTIUgBEFAAANx9a4cNQAEgUAAAAAA%3D%3D&compress=0&flag=1115422&offset=1&tosCharset=UTF8</TRRequestData></ETAInfo></etatrafficupdate>'
    send_request(request)

    print '\n\33[1m%s\33[0m\n' % ("ETAFlag=2 DataVers错误")
    request = '<etatrafficupdate Plate="京dfsff9" ContentOptions="0x3C" EtaOptions="1" Type="0x00" Flag="0x80000028" Vers="1.2" DataVers="9008"><vehicle type="0" height="2.6" load="108.9"/><path RerouteMethod="Auto"><startpoint><x>116.405090</x><y>39.988304</y></startpoint><endpoint><x>116.445755</x><y>39.832334</y></endpoint><linklens startlen="1" endlen="2"/><roadlinks IDType="0"><ID>2156659933</ID><ID>2156659879</ID><ID>2156659872</ID><ID>2156659858</ID><ID>2156659754</ID><ID>2156659767</ID><ID>2156659796</ID><ID>2156658776</ID><ID>2156658772</ID><ID>2156658797</ID><ID>2156658657</ID><ID>2156656599</ID><ID>2156656580</ID><ID>2156655706</ID><ID>2156655710</ID><ID>2156655723</ID><ID>2156655686</ID><ID>2156655683</ID><ID>2156655646</ID><ID>2156655629</ID><ID>2156655561</ID><ID>2156655591</ID><ID>2156655574</ID><ID>2156655567</ID><ID>2156655568</ID><ID>2156655196</ID><ID>2156655432</ID><ID>2156655299</ID><ID>2156649678</ID><ID>2156520567</ID><ID>2156520594</ID><ID>2156520589</ID><ID>2156520605</ID><ID>2156520620</ID><ID>2156520707</ID><ID>2156520688</ID><ID>2156520756</ID><ID>2156520773</ID><ID>2156520759</ID><ID>2156520909</ID><ID>2156520852</ID><ID>2156520826</ID><ID>2156520828</ID><ID>2156521832</ID><ID>2156521822</ID><ID>2156521798</ID><ID>2156521738</ID><ID>2156522149</ID><ID>2156522164</ID><ID>2156522172</ID><ID>2156522179</ID><ID>2156522187</ID><ID>2156522224</ID><ID>2156522230</ID><ID>2156518311</ID><ID>2156518300</ID><ID>2156518298</ID><ID>2156518213</ID><ID>2156517984</ID><ID>2156517973</ID><ID>2156517970</ID><ID>2156517958</ID><ID>2156517894</ID><ID>2156517888</ID><ID>2156517885</ID><ID>2156517882</ID><ID>2156517254</ID><ID>2156517200</ID><ID>2156517022</ID><ID>2156517014</ID><ID>2156516984</ID><ID>2156531172</ID><ID>2156531342</ID><ID>2156531351</ID><ID>2156531384</ID><ID>2156531456</ID><ID>2156534927</ID><ID>2156534932</ID><ID>2156534941</ID><ID>2156534944</ID><ID>2156534965</ID><ID>2156535172</ID><ID>2156535200</ID><ID>2156535317</ID><ID>2156535338</ID><ID>2156535340</ID><ID>2156535349</ID><ID>2156535400</ID><ID>2156535407</ID><ID>2156535413</ID><ID>2156535421</ID><ID>2156535427</ID><ID>2156535435</ID><ID>2156539534</ID><ID>2156539541</ID><ID>2156539577</ID><ID>2156539633</ID><ID>2156539638</ID><ID>2156539652</ID><ID>2156539645</ID><ID>2156539871</ID><ID>2156539877</ID><ID>2156469657</ID><ID>2156469681</ID><ID>2156470170</ID><ID>2156470210</ID><ID>2156470217</ID><ID>2156470118</ID><ID>2156470261</ID><ID>2156470278</ID><ID>2156470321</ID><ID>2156470388</ID><ID>2156470438</ID><ID>2156470463</ID><ID>2156470455</ID><ID>2156470475</ID><ID>2156470488</ID><ID>2156465612</ID><ID>2156465107</ID><ID>2156465040</ID><ID>2156465032</ID><ID>2156465011</ID><ID>2156465002</ID><ID>2156464904</ID><ID>2156476142</ID><ID>2156476134</ID><ID>2156476121</ID><ID>2156476124</ID><ID>2156475988</ID></roadlinks></path><ETAInfo><ETAFlag>2</ETAFlag><TRRequestData>cmdtype=trafficinfo&pincode=' + pincode + '&datatype=1&gpsdata=AOAVlwACADQI%2BnLqQX4LR7CBMgLcQmYGZ6JeVnn%2B%2F0sUAAA%2BA9H8%2B1gAShQAADEGGfr2SgBIFAAApwi89%2FFBAEQUAADICnz17D8AQhQAAA8NQvPnRAA%2BFAAA%2FA9u8OFFADwUAABZEhju3EIANxQAAKcU5uvXQwA7FAAAEheJ6dJHADsUAACdGQLnzUsAORQAAF8cUeTIUgBEFAAANx9a4cNQAEgUAAAAAA%3D%3D&compress=0&flag=1115422&offset=1&tosCharset=UTF8</TRRequestData></ETAInfo></etatrafficupdate>'
    send_request(request)

    print '\n\33[1m%s\33[0m\n' % ("ETAFlag=3 DataVers错误")
    request = '<etatrafficupdate Plate="京dfsff9" ContentOptions="0x3C" EtaOptions="1" Type="0x00" Flag="0x80000028" Vers="1.2" DataVers="9008"><vehicle type="0" height="2.6" load="108.9"/><path RerouteMethod="Auto"><startpoint><x>116.405090</x><y>39.988304</y></startpoint><endpoint><x>116.445755</x><y>39.832334</y></endpoint><linklens startlen="1" endlen="2"/><roadlinks IDType="0"><ID>2156659933</ID><ID>2156659879</ID><ID>2156659872</ID><ID>2156659858</ID><ID>2156659754</ID><ID>2156659767</ID><ID>2156659796</ID><ID>2156658776</ID><ID>2156658772</ID><ID>2156658797</ID><ID>2156658657</ID><ID>2156656599</ID><ID>2156656580</ID><ID>2156655706</ID><ID>2156655710</ID><ID>2156655723</ID><ID>2156655686</ID><ID>2156655683</ID><ID>2156655646</ID><ID>2156655629</ID><ID>2156655561</ID><ID>2156655591</ID><ID>2156655574</ID><ID>2156655567</ID><ID>2156655568</ID><ID>2156655196</ID><ID>2156655432</ID><ID>2156655299</ID><ID>2156649678</ID><ID>2156520567</ID><ID>2156520594</ID><ID>2156520589</ID><ID>2156520605</ID><ID>2156520620</ID><ID>2156520707</ID><ID>2156520688</ID><ID>2156520756</ID><ID>2156520773</ID><ID>2156520759</ID><ID>2156520909</ID><ID>2156520852</ID><ID>2156520826</ID><ID>2156520828</ID><ID>2156521832</ID><ID>2156521822</ID><ID>2156521798</ID><ID>2156521738</ID><ID>2156522149</ID><ID>2156522164</ID><ID>2156522172</ID><ID>2156522179</ID><ID>2156522187</ID><ID>2156522224</ID><ID>2156522230</ID><ID>2156518311</ID><ID>2156518300</ID><ID>2156518298</ID><ID>2156518213</ID><ID>2156517984</ID><ID>2156517973</ID><ID>2156517970</ID><ID>2156517958</ID><ID>2156517894</ID><ID>2156517888</ID><ID>2156517885</ID><ID>2156517882</ID><ID>2156517254</ID><ID>2156517200</ID><ID>2156517022</ID><ID>2156517014</ID><ID>2156516984</ID><ID>2156531172</ID><ID>2156531342</ID><ID>2156531351</ID><ID>2156531384</ID><ID>2156531456</ID><ID>2156534927</ID><ID>2156534932</ID><ID>2156534941</ID><ID>2156534944</ID><ID>2156534965</ID><ID>2156535172</ID><ID>2156535200</ID><ID>2156535317</ID><ID>2156535338</ID><ID>2156535340</ID><ID>2156535349</ID><ID>2156535400</ID><ID>2156535407</ID><ID>2156535413</ID><ID>2156535421</ID><ID>2156535427</ID><ID>2156535435</ID><ID>2156539534</ID><ID>2156539541</ID><ID>2156539577</ID><ID>2156539633</ID><ID>2156539638</ID><ID>2156539652</ID><ID>2156539645</ID><ID>2156539871</ID><ID>2156539877</ID><ID>2156469657</ID><ID>2156469681</ID><ID>2156470170</ID><ID>2156470210</ID><ID>2156470217</ID><ID>2156470118</ID><ID>2156470261</ID><ID>2156470278</ID><ID>2156470321</ID><ID>2156470388</ID><ID>2156470438</ID><ID>2156470463</ID><ID>2156470455</ID><ID>2156470475</ID><ID>2156470488</ID><ID>2156465612</ID><ID>2156465107</ID><ID>2156465040</ID><ID>2156465032</ID><ID>2156465011</ID><ID>2156465002</ID><ID>2156464904</ID><ID>2156476142</ID><ID>2156476134</ID><ID>2156476121</ID><ID>2156476124</ID><ID>2156475988</ID></roadlinks></path><ETAInfo><ETAFlag>3</ETAFlag><TRRequestData>cmdtype=trafficinfo&pincode=' + pincode + '&datatype=1&gpsdata=AOAVlwACADQI%2BnLqQX4LR7CBMgLcQmYGZ6JeVnn%2B%2F0sUAAA%2BA9H8%2B1gAShQAADEGGfr2SgBIFAAApwi89%2FFBAEQUAADICnz17D8AQhQAAA8NQvPnRAA%2BFAAA%2FA9u8OFFADwUAABZEhju3EIANxQAAKcU5uvXQwA7FAAAEheJ6dJHADsUAACdGQLnzUsAORQAAF8cUeTIUgBEFAAANx9a4cNQAEgUAAAAAA%3D%3D&compress=0&flag=1115422&offset=1&tosCharset=UTF8</TRRequestData></ETAInfo></etatrafficupdate>'
    send_request(request)

    # 请求TR的路况验证， 路况固定时间20160925173000，拥堵距离5997， TR折算成6公里，对应route请求：<route Source="amap" Flag="0x800000281" Type="0x00" ContentOptions="0x10" Vers="4.0" SdkVer="3.6.8.1.1.20160510.30306.1517"><startpoint><x>116.383240</x><y>39.857033</y></startpoint><endpoint><x>116.460384</x><y>39.867596</y></endpoint></route>
    #print ""
    #request = '<etatrafficupdate Plate="京dfsff9" ContentOptions="0x3C" EtaOptions="1" Type="0x00" Flag="0x800000281" Vers="1.2" DataVers="'+ str(data_version) + '"><vehicle type="0" height="6.4" load="13.2"/><path RerouteMethod="Auto"><startpoint><x>116.383240</x><y>39.857033</y></startpoint><endpoint><x>116.460384</x><y>39.867596</y></endpoint><linklens startlen="1" endlen="2"/><roadlinks IDType="0"><ID>2156806226</ID><ID>2156806340</ID><ID>2156806327</ID><ID>2156806505</ID><ID>2156806493</ID><ID>2156482812</ID><ID>2156482759</ID><ID>2156482763</ID><ID>2156482742</ID><ID>2156482730</ID><ID>2156482697</ID><ID>2156482588</ID><ID>2156482520</ID><ID>2156482516</ID><ID>2156482500</ID><ID>2156482445</ID><ID>2156480756</ID><ID>2156480724</ID><ID>2156481004</ID><ID>2156481104</ID><ID>2156481111</ID><ID>2156481126</ID><ID>2156481300</ID><ID>2156473515</ID><ID>2156473527</ID><ID>2156473405</ID><ID>2156473389</ID><ID>2156473359</ID><ID>2156473814</ID><ID>2156473929</ID><ID>2156473923</ID><ID>2156473956</ID><ID>2156473999</ID><ID>2156472241</ID><ID>2156472250</ID><ID>2156472282</ID><ID>2156472069</ID><ID>2156472126</ID><ID>2156472043</ID><ID>2156472038</ID><ID>2156472032</ID><ID>2156472024</ID><ID>2156471906</ID><ID>2156471921</ID><ID>2156471927</ID><ID>2156471930</ID><ID>2156471936</ID><ID>2156471835</ID><ID>2156471831</ID><ID>2156471790</ID></roadlinks></path><ETAInfo><ETAFlag>2</ETAFlag><TRRequestData>cmdtype=trafficinfo&pincode=' + pincode + '&datatype=1&gpsdata=AOAVlwACADQI%2BnLqQX4LR7CBMgLcQmYGZ6JeVnn%2B%2F0sUAAA%2BA9H8%2B1gAShQAADEGGfr2SgBIFAAApwi89%2FFBAEQUAADICnz17D8AQhQAAA8NQvPnRAA%2BFAAA%2FA9u8OFFADwUAABZEhju3EIANxQAAKcU5uvXQwA7FAAAEheJ6dJHADsUAACdGQLnzUsAORQAAF8cUeTIUgBEFAAANx9a4cNQAEgUAAAAAA%3D%3D&compress=0&flag=1115422&offset=1&tosCharset=UTF8</TRRequestData></ETAInfo></etatrafficupdate>'
    #send_request(request)

    print '\n\33[1m%s\33[0m\n' % ("pincode过期 播报内容返回固定字节数（161bytes）")
    request = '<etatrafficupdate Plate="京dfsff9" ContentOptions="0x3C" EtaOptions="1" Type="0x00" Flag="0x80000028" Vers="1.2" DataVers="'+ str(data_version) + '"><vehicle type="0" height="2.6" load="108.9"/><path RerouteMethod="Auto"><startpoint><x>116.405090</x><y>39.988304</y></startpoint><endpoint><x>116.445755</x><y>39.832334</y></endpoint><linklens startlen="1" endlen="2"/><roadlinks IDType="0"><ID>2156659933</ID><ID>2156659879</ID><ID>2156659872</ID><ID>2156659858</ID><ID>2156659754</ID><ID>2156659767</ID><ID>2156659796</ID><ID>2156658776</ID><ID>2156658772</ID><ID>2156658797</ID><ID>2156658657</ID><ID>2156656599</ID><ID>2156656580</ID><ID>2156655706</ID><ID>2156655710</ID><ID>2156655723</ID><ID>2156655686</ID><ID>2156655683</ID><ID>2156655646</ID><ID>2156655629</ID><ID>2156655561</ID><ID>2156655591</ID><ID>2156655574</ID><ID>2156655567</ID><ID>2156655568</ID><ID>2156655196</ID><ID>2156655432</ID><ID>2156655299</ID><ID>2156649678</ID><ID>2156520567</ID><ID>2156520594</ID><ID>2156520589</ID><ID>2156520605</ID><ID>2156520620</ID><ID>2156520707</ID><ID>2156520688</ID><ID>2156520756</ID><ID>2156520773</ID><ID>2156520759</ID><ID>2156520909</ID><ID>2156520852</ID><ID>2156520826</ID><ID>2156520828</ID><ID>2156521832</ID><ID>2156521822</ID><ID>2156521798</ID><ID>2156521738</ID><ID>2156522149</ID><ID>2156522164</ID><ID>2156522172</ID><ID>2156522179</ID><ID>2156522187</ID><ID>2156522224</ID><ID>2156522230</ID><ID>2156518311</ID><ID>2156518300</ID><ID>2156518298</ID><ID>2156518213</ID><ID>2156517984</ID><ID>2156517973</ID><ID>2156517970</ID><ID>2156517958</ID><ID>2156517894</ID><ID>2156517888</ID><ID>2156517885</ID><ID>2156517882</ID><ID>2156517254</ID><ID>2156517200</ID><ID>2156517022</ID><ID>2156517014</ID><ID>2156516984</ID><ID>2156531172</ID><ID>2156531342</ID><ID>2156531351</ID><ID>2156531384</ID><ID>2156531456</ID><ID>2156534927</ID><ID>2156534932</ID><ID>2156534941</ID><ID>2156534944</ID><ID>2156534965</ID><ID>2156535172</ID><ID>2156535200</ID><ID>2156535317</ID><ID>2156535338</ID><ID>2156535340</ID><ID>2156535349</ID><ID>2156535400</ID><ID>2156535407</ID><ID>2156535413</ID><ID>2156535421</ID><ID>2156535427</ID><ID>2156535435</ID><ID>2156539534</ID><ID>2156539541</ID><ID>2156539577</ID><ID>2156539633</ID><ID>2156539638</ID><ID>2156539652</ID><ID>2156539645</ID><ID>2156539871</ID><ID>2156539877</ID><ID>2156469657</ID><ID>2156469681</ID><ID>2156470170</ID><ID>2156470210</ID><ID>2156470217</ID><ID>2156470118</ID><ID>2156470261</ID><ID>2156470278</ID><ID>2156470321</ID><ID>2156470388</ID><ID>2156470438</ID><ID>2156470463</ID><ID>2156470455</ID><ID>2156470475</ID><ID>2156470488</ID><ID>2156465612</ID><ID>2156465107</ID><ID>2156465040</ID><ID>2156465032</ID><ID>2156465011</ID><ID>2156465002</ID><ID>2156464904</ID><ID>2156476142</ID><ID>2156476134</ID><ID>2156476121</ID><ID>2156476124</ID><ID>2156475988</ID></roadlinks></path><ETAInfo><ETAFlag>2</ETAFlag><TRRequestData>cmdtype=trafficinfo&pincode=AN_Amap_IOS_FC_af2fd784-a94c-438f-b8b1-12f51327342c&datatype=1&gpsdata=AOAVlwACADQI%2BnLqQX4LR7CBMgLcQmYGZ6JeVnn%2B%2F0sUAAA%2BA9H8%2B1gAShQAADEGGfr2SgBIFAAApwi89%2FFBAEQUAADICnz17D8AQhQAAA8NQvPnRAA%2BFAAA%2FA9u8OFFADwUAABZEhju3EIANxQAAKcU5uvXQwA7FAAAEheJ6dJHADsUAACdGQLnzUsAORQAAF8cUeTIUgBEFAAANx9a4cNQAEgUAAAAAA%3D%3D&compress=0&flag=1115422&offset=1&tosCharset=UTF8</TRRequestData></ETAInfo></etatrafficupdate>'
    send_request(request)


    print '\n12313214123412341234s\n'

    request = '<etatrafficupdate Plate="京dfsff9" ContentOptions="0x3C" EtaOptions="1" Type="0x00" Flag="0x800000281" Vers="1.2" DataVers="55120"><path RerouteMethod="Auto"><startpoint><x>116.444800</x><y>39.964104</y></startpoint><endpoint><x>116.444049</x><y>39.858945</y></endpoint><linklens startlen="1" endlen="2"/><roadlinks IDType="0"><ID>2156597738</ID><ID>2156597619</ID><ID>2156597632</ID><ID>2156597635</ID><ID>2156597564</ID><ID>2156597571</ID><ID>2156597574</ID><ID>2156597579</ID><ID>2156597553</ID><ID>2156597543</ID><ID>2156597545</ID><ID>2156597536</ID><ID>2156597535</ID><ID>2156607725</ID><ID>2156607673</ID><ID>2156607668</ID><ID>2156607921</ID><ID>2156607510</ID><ID>2156607438</ID><ID>2156607437</ID><ID>2156607368</ID><ID>2156607242</ID><ID>2156607246</ID><ID>2156607257</ID><ID>2156607310</ID><ID>2156607301</ID><ID>2156607295</ID><ID>2156603853</ID><ID>2156603999</ID><ID>2156603665</ID><ID>2156603614</ID><ID>2156603611</ID><ID>2156603691</ID><ID>2156603534</ID><ID>2156620751</ID><ID>2156620832</ID><ID>2156620829</ID><ID>2156620828</ID><ID>2156620824</ID><ID>2156620873</ID><ID>2156621127</ID><ID>2156621119</ID><ID>2156621790</ID><ID>2156621753</ID><ID>2156622104</ID><ID>2156622221</ID><ID>2156624519</ID><ID>2156624570</ID><ID>2156624576</ID><ID>2156624701</ID><ID>2156624846</ID><ID>2156624851</ID><ID>2156624931</ID><ID>2156625077</ID><ID>2156626240</ID><ID>2156626248</ID><ID>2156626252</ID><ID>2156626290</ID><ID>2156626300</ID><ID>2156626348</ID><ID>2156626704</ID><ID>2156626705</ID><ID>2156626718</ID><ID>2156626790</ID><ID>2156626874</ID><ID>2156626869</ID><ID>2156626883</ID><ID>2156626850</ID><ID>2156559546</ID><ID>2156559587</ID><ID>2156559593</ID><ID>2156559690</ID><ID>2156559688</ID><ID>2156559679</ID><ID>2156559660</ID><ID>2156559664</ID><ID>2156559780</ID><ID>2156559790</ID><ID>2156559794</ID><ID>2156559801</ID><ID>2156559880</ID><ID>2156559825</ID><ID>2156560040</ID></roadlinks></path><ETAInfo><ETAFlag>2</ETAFlag><TRRequestData>cmdtype=trafficinfo&pincode=AN_Amap_IOS_FC_e5343ad9-ac6a-4910-ac55-3164667b3f45&datatype=1&gpsdata=AOAVlwACADQI%2BnLqQX4LR7CBMgLcQmYGZ6JeVnn%2B%2F0sUAAA%2BA9H8%2B1gAShQAADEGGfr2SgBIFAAApwi89%2FFBAEQUAADICnz17D8AQhQAAA8NQvPnRAA%2BFAAA%2FA9u8OFFADwUAABZEhju3EIANxQAAKcU5uvXQwA7FAAAEheJ6dJHADsUAACdGQLnzUsAORQAAF8cUeTIUgBEFAAANx9a4cNQAEgUAAAAAA%3D%3D&compress=0&flag=1115422&offset=1&tosCharset=UTF8</TRRequestData></ETAInfo></etatrafficupdate>'
    #request = '<etatrafficupdate Plate="京dfsff9" ContentOptions="0x3C" EtaOptions="1" Type="0x00" Flag="0x800000281" Vers="1.2" DataVers="55120"><path RerouteMethod="Auto"><startpoint><x>116.444800</x><y>39.964104</y></startpoint><endpoint><x>116.444049</x><y>39.858945</y></endpoint><linklens startlen="1" endlen="2"/><roadlinks IDType="0"><ID>2156597738</ID><ID>2156597619</ID><ID>2156597632</ID><ID>2156597635</ID><ID>2156597564</ID><ID>2156597571</ID><ID>2156597574</ID><ID>2156597579</ID><ID>2156597553</ID><ID>2156597543</ID><ID>2156597545</ID><ID>2156597536</ID><ID>2156597535</ID><ID>2156607725</ID><ID>2156607673</ID><ID>2156607668</ID><ID>2156607921</ID><ID>2156607510</ID><ID>2156607438</ID><ID>2156607437</ID><ID>2156607368</ID><ID>2156607242</ID><ID>2156607246</ID><ID>2156607257</ID><ID>2156607310</ID><ID>2156607301</ID><ID>2156607295</ID><ID>2156603853</ID><ID>2156603999</ID><ID>2156603665</ID><ID>2156603614</ID><ID>2156603611</ID><ID>2156603691</ID><ID>2156603534</ID><ID>2156620751</ID><ID>2156620832</ID><ID>2156620829</ID><ID>2156620828</ID><ID>2156620824</ID><ID>2156620873</ID><ID>2156621127</ID><ID>2156621119</ID><ID>2156621790</ID><ID>2156621753</ID><ID>2156622104</ID><ID>2156622221</ID><ID>2156624519</ID><ID>2156624570</ID><ID>2156624576</ID><ID>2156624701</ID><ID>2156624846</ID><ID>2156624851</ID><ID>2156624931</ID><ID>2156625077</ID><ID>2156626240</ID><ID>2156626248</ID><ID>2156626252</ID><ID>2156626290</ID><ID>2156626300</ID><ID>2156626348</ID><ID>2156626704</ID><ID>2156626705</ID><ID>2156626718</ID><ID>2156626790</ID><ID>2156626874</ID><ID>2156626869</ID><ID>2156626883</ID><ID>2156626850</ID><ID>2156559546</ID><ID>2156559587</ID><ID>2156559593</ID><ID>2156559690</ID><ID>2156559688</ID><ID>2156559679</ID><ID>2156559660</ID><ID>2156559664</ID><ID>2156559780</ID><ID>2156559790</ID><ID>2156559801</ID><ID>2156559880</ID><ID>2156559825</ID><ID>2156560040</ID></roadlinks></path><ETAInfo><ETAFlag>2</ETAFlag><TRRequestData>cmdtype=trafficinfo&pincode=AN_Amap_IOS_FC_e5343ad9-ac6a-4910-ac55-3164667b3f45&datatype=1&gpsdata=AOAVlwACADQI%2BnLqQX4LR7CBMgLcQmYGZ6JeVnn%2B%2F0sUAAA%2BA9H8%2B1gAShQAADEGGfr2SgBIFAAApwi89%2FFBAEQUAADICnz17D8AQhQAAA8NQvPnRAA%2BFAAA%2FA9u8OFFADwUAABZEhju3EIANxQAAKcU5uvXQwA7FAAAEheJ6dJHADsUAACdGQLnzUsAORQAAF8cUeTIUgBEFAAANx9a4cNQAEgUAAAAAA%3D%3D&compress=0&flag=1115422&offset=1&tosCharset=UTF8</TRRequestData></ETAInfo></etatrafficupdate>'
    send_request(request)

if __name__ == "__main__":
    #count = 100000
    #while count > 0:
    #    run()
    #    time.sleep(1)
    #    count -= 1
    run()